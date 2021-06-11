#include "minishell.h"

void redirect_check(t_command *com)
{
	t_command *start;

	//printf_command_list(com);
	start = com;
	while (start)
	{
		if (start->command[0] == '>' && start->command[1] == '>')
		{
			com->redir_double_right = ft_strdup(start->next->command);
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
			com->redir_right = ft_strdup(start->next->command);
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
			com->redir_left = ft_strdup(start->next->command);
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
		while (start)
		{
			//printf("dsfsdfsd*************\n");
			//printf("start->command  = %s\n", start->command );
			start->command = replace_dollar_que_into_code(start->command, untils);
			//printf("dsfsdfsd+++\n");
			start = start->next;
		}
		start = com;
		if (check_buildin(start->command))
		{
			ft_free(untils->command_ex);
			untils->command_ex = ft_strdup_b(start->command);
			int process[1];
			process[0] = fork();
			if (process[0] == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				// signal(SIGINT, SIG_IGN);
				// signal(SIGTERM, SIG_IGN);
				// signal(SIGQUIT, SIG_IGN);
				
				if (check_bin(start->command))
				{
					if (!check_redir(start, 2, untils))
						exit(1);
					work_bin(start, untils);
				}
				if (!(find_path(untils)) && !(check_bin(start->command)))
				{
					printf("123\n");
					exit(127);
				}
			// {
			// 	work_bin(start, untils);
			
			// start = start->next;
			ft_free(untils->path);
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
			char *command;
			command = NULL;
			int id;
			// id = fork();
			start = com;
			// int process[1];
			// process[0] = fork();
			if (process[0] == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				// signal(SIGINT, SIG_IGN);
				// signal(SIGTERM, SIG_IGN);
				// signal(SIGQUIT, SIG_IGN);
				//дочка
				char *commd;
				commd = ft_strjoin_line("/", untils->command_ex);
				if (!check_redir(start, 2, untils))
					exit(1);
				while(bin[i] != NULL)
				{
					command = ft_strjoin_line(bin[i], commd);
					//проверка на наличие PATH;
					if (execve(command, arguments, untils->env) == 0)
					{
						printf("make\n");
						ft_free(command);
						break ;
					}
					ft_free(command);
					i++;
				}
				ft_free(commd);
				if (bin[i] == NULL && ft_strcmp(untils->command_ex, "minishell") && ft_strcmp(untils->command_ex, "./minishell") && ft_strcmp(untils->command_ex, "$?"))
				{
					printf("123222\n");
					exit(127);
				}
				if (!(ft_strcmp(untils->command_ex, "$?")))
				{
					printf("0 : command not found");
					exit(127);
				}
			}
			}
			else
			{
				waitpid(process[0], &untils->status, 0);
				untils->status = untils->status / 256;
				if (untils->status == 127 && ft_strcmp(untils->command_ex, "$?"))
					printf("command not found\n");
			}
		}
			// int p;
			// p = 0;
			// while (arguments[p] != 0)
			// {
			// 	ft_free(arguments[p]);
			// 	p++;
			// }
			// ft_free(arguments);
			// p = 0;
			// while (bin[p] != 0)
			// {
			// 	ft_free(bin[p]);
			// 	p++;
			// }
			// ft_free(bin);
		else
		{
			bsophia_function(com, untils);
			// printf("!! %d\n", untils->status);
		}
	}
	else
	{

		int status;
		int j = 0;
		t_command **command_pipes;
		t_command *current_pipe = 0;

		command_pipes =  (t_command **)malloc(sizeof(t_command*) * (count_pipes + 1));
		command_pipes[count_pipes] = 0;
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
				ft_lstadd_back_parser(&current_pipe, ft_lstnew_parser(ft_strdup_b(start->command), 0));
			}
			start = start->next;
		}
		if (current_pipe != 0)
		{
			command_pipes[j] = current_pipe;
		}
		int pipes[count_pipes][2];
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
			process[j] = fork();
			if (process[j] == 0)
			{
				// signal(SIGINT, SIG_IGN);
				// signal(SIGTERM, SIG_IGN);
				// signal(SIGQUIT, SIG_IGN);
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				connect_stdio_to_pipes(prev_pipe_fds, next_pipe_fds);
				work_pipes(untils, command_pipes[i]);
			}
			close(prev_pipe_fds[0]);
			close(prev_pipe_fds[1]);
			i++;
			j++;
		}
		j = 0;
		while (j < count_pipes + 1)
		{
			waitpid(process[j], &(untils->status), 0);
			untils->status = untils->status / 256;
			if (untils->status == 127)
				printf("%s: command not found\n", command_pipes[j]->command);
			j++;
		}
		j = 0;
		while (j < count_pipes + 1)
		{
			ft_lstclear_command(&command_pipes[j]);
			j++;
		}
		ft_free(command_pipes);
	}
}

void main_parser(char *str, t_untils *untils)
{
	t_command	*start;
	t_command	*current_command;

	start = 0;
	start = parser_into_list(str, untils);
	if (start != 0 )//&& start->command[0] == 'e' && start->command[1] == 'r')
		printf("%s\n", start->command);
	ft_free(start);
}
