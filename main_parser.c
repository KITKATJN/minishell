#include "minishell.h"



void redirect_check(t_command *com)
{
	t_command *start;

	start = com;
	while (start)
	{
		if (start->command[0] == '>' && start->command[1] == '>')
		{
			com->redir_double_right = start->next->command;
			int gf = open(com->redir_double_right, O_CREAT | O_WRONLY | O_APPEND, 0777);
			close (gf);
			delete_current_parser(start->next);
			if (start->back != 0)
			{
				start = start->back;
				delete_current_parser(start->next);
			}
			else
			{
				start = start->next;
				if (start)
				{
					delete_current_parser(start->back);
					start->back = 0;
				}
			}
		}
		else if (start->command[0] == '>')
		{
			com->redir_right = start->next->command;
			int ff = open(com->redir_right, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			close (ff);
			delete_current_parser(start->next);
			if (start->back != 0)
			{
				start = start->back;
				delete_current_parser(start->next);
			}
			else
			{
				start = start->next;
				if (start)
				{
					delete_current_parser(start->back);
					start->back = 0;
				}
			}
		}
		else if (start->command[0] == '<')
		{
			com->redir_left = start->next->command;
			int gg = open(com->redir_left, O_RDWR);
			close(gg);
			delete_current_parser(start->next);
			if (start->back != 0)
			{
				start = start->back;
				delete_current_parser(start->next);
			}
			else
			{
				start = start->next;
				if (start)
				{
					delete_current_parser(start->back);
					start->back = 0;
				}
			}
		}
		start = start->next;
	}
}

void	func(t_command *current_pipe)
{
	int i = 0;
	while (current_pipe)
	{
		printf("func %s\n", current_pipe->command);
		current_pipe = current_pipe->next;
	}
}

void connect_stdio_to_pipes(int prev_fds[], int next_fds[])
{
    if (prev_fds[0] >= 0)
    {
        dup2(prev_fds[0], 0);
        close(prev_fds[0]);
        close(prev_fds[1]);
    }
    if (next_fds[1] >= 0)
    {
        dup2(next_fds[1], 1);
        close(next_fds[1]);
        close(next_fds[0]);
    }
}

void bsopia_func(t_command *com, int i, t_untils *untils)
{
	t_command *start;

	start = com;
	int count_pipes = 0;
	while (start)
	{
		if (start->command[0] == '|')
			count_pipes++;
		start = start->next;
	}
	// printf("%d\n", count_pipes);
	start = com;
	if (count_pipes == 0)
	{
		redirect_check(com);
		// while (start) // echo pl | echo hgfda123 | echo 456
		// 	{
		// 		printf("%s  dr = %s  right = %s left = %s ->%d\n", start->command, start->redir_double_right, start->redir_right, start->redir_left, i);
		// 		start = start->next;
		// 	}
		if (check_buildin(start->command))
		{
			untils->command_ex = ft_strdup_b(start->command);
			// start = start->next;
			untils->path = find_path(untils);
			char **bin = ft_split(untils->path, ':');
			char **arguments;
			int i = 0;
			while (start)
			{
				start = start->next;
				i++;
			}
			arguments = (char**)malloc(i * sizeof(char*) + 1);
			start = com;
			i = 0;
			while (start)
			{
				arguments[i] = ft_strdup_b(start->command);
				start = start->next;
				i++;
			}
			arguments[i] = NULL;
			i = 0;
			int id;
			id = fork();
			char *command;
			command = NULL;
			start = com;
			if (id == 0)
			{
				//дочка
				char *commd;
				commd = ft_strjoin_line("/", untils->command_ex);
				check_redir(start, 2, untils);
				while(bin[i] != NULL)
				{
					command = ft_strjoin_line(bin[i], commd);
					if (execve(command, arguments, untils->env) == 0)
						break ;
					i++;
				}
			}
			else
				wait(0);
		}
		else
			bsophia_function(com, untils);
	}
	else
	{
		// int tmpin = dup(0);
		// int tmpout = dup(1);
		// int **pipes;
		// int *process;
		int status;
		int j = 0;
		t_command **command_pipes;
		t_command *current_pipe = 0;
		
		command_pipes =  (t_command **)malloc(sizeof(t_command*) * (count_pipes + 1));
		j = 0;
		while (start)
		{
			if (start->command[0] == '|')
			{
				command_pipes[j] = current_pipe;
				current_pipe = 0;
				j++;
			}
			else
			{
				ft_lstadd_back_parser(&current_pipe, ft_lstnew_parser(start->command, 0));
			}
			start = start->next;
		}
		if (current_pipe != 0)
		{
			command_pipes[j] = current_pipe;
		}
		int pipes[count_pipes][2];
		
		// pipes = (int **)malloc(sizeof(int*) * (count_pipes + 1));
		// j = 0;
		// while (j < count_pipes)
		// {
		// 	pipes[j] = malloc(sizeof(int) * 2);
		// 	j++;
		// }
		j = 0;
		int process[count_pipes + 1];
		int prev_pipe_fds[2];
		int next_pipe_fds[2];
		next_pipe_fds[0] = -1;
		next_pipe_fds[1] = -1;
		while (i < count_pipes + 1)
		{
			prev_pipe_fds[0] = next_pipe_fds[0];
			prev_pipe_fds[1] = next_pipe_fds[1];
			if (i != count_pipes)
			{
				pipe(next_pipe_fds);
			}
			else
			{
				next_pipe_fds[0] = -1;
				next_pipe_fds[1] = -1;
			}
			if (fork() == 0)
			{
				// printf("%s\n", command_pipes[i]->command);
				connect_stdio_to_pipes(prev_pipe_fds, next_pipe_fds);
				work_pipes(untils, command_pipes[i]);
				// char **cmd = cmds[i];
				// execve(cmd[0], cmd, NULL);
			}
			close(prev_pipe_fds[0]);
			close(prev_pipe_fds[1]);
			i++;
		}
		j = 0;
		while (j < count_pipes + 1)
		{
			waitpid(-1, &(status), 0);
			j++;
		}
		// wait(NULL);
		// wait(NULL);
		// wait(NULL);
		// wait(NULL);
		// return (0);
		// process = malloc(sizeof(int) * (count_pipes + 1));
		// while (j < count_pipes + 1)
		// {
		// 	// printf("j %d\n", j);
		// 	if (j < count_pipes)
		// 	{
		// 		pipe(pipes[j]);
		// 	}
		// 	process[j] = fork();
		// 	if (process[j] == 0)
		// 	{
				
		// 		if (j == 0)
		// 		{
					
		// 			dup2(pipes[j][1], STDOUT_FILENO);
		// 			close(pipes[j][1]);
		// 			close(pipes[0][0]);
		// 			work_pipes(untils, command_pipes[j]);
		// 			// exit(0);
		// 		}
		// 		else if (j != count_pipes)
		// 		{
					
		// 			dup2(pipes[j - 1][0], STDIN_FILENO);
		// 			dup2(pipes[j][1], STDOUT_FILENO);
		// 			close(pipes[j-1][0]);
		// 			close(pipes[j - 1][1]);
		// 			close(pipes[j][1]);//что мыы закрываем?
		// 			close(pipes[j][0]);
		// 			work_pipes(untils, command_pipes[j]);
		// 			//вывзываем нашу функцию
		// 			// exit(0);
		// 		}
		// 		else
		// 		{
		// 			dup2(pipes[j - 1][0], STDIN_FILENO);
		// 			close(pipes[j - 1][0]);
		// 			close(pipes[j -1][1]);
		// 			work_pipes(untils, command_pipes[j]);
		// 			// exit(0);
		// 		}
		// 			//last
		// 	}
		// 	close(pipes[j][0]);
		// 	close(pipes[j][1]);
		// 	// else
		// 	// 	wait(0);
		// 	// waitpid(process[j], &(status), 0);
		// 	j++;
		// 	printf("bla %d\n", j);
		// //просто дописать пацпы в самом конце]/ перед сдачей
		// }
		// j = 0;
		// while (j < count_pipes + 1)
		// {
		// 	waitpid(process[j], &(status), 0);
		// 	j++;
		// }
		// printf("CSD\n");
		// j = 0;
		// while (j < count_pipes + 1)
		// {
		// 	waitpid(process[j], &status, NULL);
		// 	j++;
		// }
	j = 0;
	// dup2(tmpout, 1);
	// dup2(tmpin, 0);
	// close(tmpout);
	// close(tmpin);
	// // while (com)
	// // {
	// // 	printf("%s  dr = %s  right = %s left = %s ->%d\n", com->command, com->redir_double_right, com->redir_right, com->redir_left, i);
	// // 	com = com->next;
	// // }
	// }
	}
}

void main_parser(char *str, t_untils *untils)
{
	t_command	*start;
	t_command	*current_command;

	start = 0;
	start = parser_into_list_2(str, untils);
}
