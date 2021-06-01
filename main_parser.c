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
			open(com->redir_double_right, O_CREAT | O_WRONLY | O_APPEND, 0777);
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
			int gg = open(com->redir_left, O_WRONLY | 0777);
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
		int tmpin = dup(0);
		int tmpout = dup(1);
		int **pipes;
		int *process;
		int j = 0;
		t_command **command_pipes;
		t_command *current_pipe = 0;

		command_pipes =  (t_command **)malloc(sizeof(t_command*) * (count_pipes + 1));
		j =0;
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
		pipes = (int **)malloc(sizeof(int*) * (count_pipes + 1));
		j = 0;
		while (j < count_pipes)
		{
			pipes[j] = malloc(sizeof(int) * 2);
			j++;
		}
		j = 0;
		process = malloc(sizeof(int) * count_pipes + 1);
		while (j < count_pipes + 1)
		{
			if (j < count_pipes)
				pipe(pipes[j]);
			process[j] = fork();
			if (process[j] == 0)
			{
				if (j == 0)
				{
					dup2(pipes[0][1], STDOUT_FILENO);
					close(pipes[0][1]);
					work_pipes(untils, command_pipes[j]);
					exit(0);
				}
				else if (j != count_pipes)
					{
						dup2(pipes[j - 1][0], STDIN_FILENO);
						dup2(pipes[j][1], STDOUT_FILENO);
						close(pipes[j-1][0]);
						close(pipes[j][1]);//что мыы закрываем?
						work_pipes(untils, command_pipes[j]);
						//вывзываем нашу функцию
						exit(0);
					}
				else
				{
					dup2(pipes[j - 1][0], STDIN_FILENO);
					close(pipes[j-1][0]);
					work_pipes(untils, command_pipes[j]);
				}
					//last
			}
			else
				wait(0);
			j++;
		//просто дописать пацпы в самом конце]/ перед сдачей
		}
	j = 0;
	while (j < count_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	dup2(tmpout, 1);
	dup2(tmpin, 0);
	close(tmpout);
	close(tmpin);
	// while (com)
	// {
	// 	printf("%s  dr = %s  right = %s left = %s ->%d\n", com->command, com->redir_double_right, com->redir_right, com->redir_left, i);
	// 	com = com->next;
	// }
	}
}

void main_parser(char *str, t_untils *untils)
{
	t_command	*start;
	t_command	*current_command;

	start = 0;
	//start = parser_into_list("echo  -n     'y   sdf jghmj' \"f d!!!fs;ds\"  h    ff;vx sdf ft        mkk");
	//start = parser_into_list("echo $PWD$PATH;echo  -n $t rgdfg HELLO$t $s1 'hgf $PATH' \"    ;$t$PATH\";export\" fsd; hjghj;;$PATH\"  ry rt $bf;   echo 'echo'\"hello\"");
	//printf("-------------->main parser !%s!\n", str);
	start = parser_into_list_2(str, untils);
	//printf("%s\n", start->command);
	//bsophia_function(start, untils);
	// if (str != 0)
	// {
	// 	start = parser_into_list(str);
	// 	if (start->flag != 0 && !ft_strncmp("error", start->flag, ft_strlen("error")))
	// 	{
	// 		ft_perror(start->command);
	// 	}
	// 	pars_to_command(start);
	// 	parse_add_semicolon_to_end(start);
	// 	current_command = start;
	// }
	// else
	// 	start = ft_lstnew_parser("", 0);

	// current_command = start;
	// int i = 1;
	// t_command *new_start = 0;
	// t_command *new_command;
	// while (current_command)
	// {
	// 	if (current_command->command[0] == ';')
	// 	{
	// 		bsopia_func(new_start, i++, untils);
	// 		new_start = 0;
	// 		current_command = current_command->next;
	// 		if (current_command == 0)
	// 			break ;
	// 	}
	// 	//printf("1---------------------------------------\n");
	// 	new_command = ft_lstnew_parser(ft_strdup(current_command->command), 0);
	// 	//printf("2---------------------------------------\n");
	// 	ft_lstadd_back_parser(&new_start, new_command);
	// 	//printf("3---------------------------------------\n");
	// 	current_command = current_command->next;
	// }
	// if (new_start)
	// {
	// 	//printf("OMG\n");
	// 	bsopia_func(new_start, i++, untils);
	// 	new_start = 0;
	// }
}
