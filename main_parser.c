#include "minishell.h"

void ft_paste_env(t_command *list_of_command)
{
	t_command	*start;
	char		*start_command;
	char		*env;
	char		*back_env;
	char		*value_env;
	char		*tmp;
	int			i;
	int			j;

	start = list_of_command;
	while (start)
	{
		i = 0;
		while (start->command[i] != '\0')
		{
			if (start->command[i] == '\'' && start->command[0] != '\"')
				break ;
			if (start->command[i] == '$')
			{
				start_command = ft_substr(start->command, 0, i);
				j = i;
				i++;
				while (start->command[i] != '\0' && start->command[i] != ' ' && start->command[i] != '$' && start->command[i] != '\"')
					i++;
				env = ft_substr(start->command, j + 1, i - j - 1);
				back_env = ft_substr(start->command, j + 1 + i - j - 1, ft_strlen(start->command));
				//printf("!!!!!!!!!!!env = !%s! back = %s   %s %d\n", env, back_env, start->command, i-j-2);
				if (getenv(env) == 0)
				{
					free(env);
					env = ft_substr(start->command, 0 , j);
					free(start->command);
					start->command = ft_strjoin(env, back_env);
					free(env);
					i = 0;
					continue ;
				}
				value_env = ft_strdup(getenv(env));
				free(env);
				free(start->command);
				if (start_command[0] == '\"')
				{
					env = ft_strjoin(start_command, value_env);
					start->command = ft_strjoin(env, back_env);
					free(env);
				}
				else
				{
					tmp = ft_strjoin(start_command, value_env);
					start->command = ft_strjoin(tmp, back_env);
					free(tmp);
				}
				free(start_command);
				free(value_env);
				if (start->command[0] == '\"')
					continue ;
				// printf("----->%c\n", start->command[i]);
				continue ;
				//else
				//	break ;
			}
			i++;
		}
		if (start->command[0] == '\"' && start->command[ft_strlen(start->command) - 1] != '\"')
		{
			tmp = ft_strjoin(start->command, "\"");
			free(start->command);
			start->command = tmp;
		}
		start = start->next;
	}

}

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
			open(com->redir_right, O_CREAT | O_WRONLY | O_TRUNC, 0777);
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

	int tmpin2 = dup(0);
	int tmpout2 = dup(1);
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
		if (check_buildin(start->command))
		{
			untils->command_ex = ft_strdup_b(start->command);
			start = start->next;
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
			// start = start->next;
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
				exit(0);
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

		t_command *start_pipes = 0;
		start = com;
		int ret;
		int fdout;
		while (start)
		{
			if (start->command[0] == '|')
			{
				redirect_check(start_pipes);
				int fdin;
				if (start_pipes->redir_left != 0)
					fdin = open(start_pipes->redir_left, O_WRONLY | 0777);
				else
					fdin = dup(tmpin);
				dup2(fdin, 0);
				close(fdin);

				int fd[2];
				pipe(fd);
				fdout = fd[1];
				fdin = fd[0];
				//printf("1--------------\n");
				dup2(fdout, 1);
				close(fdout);
				ret = fork();
				//printf("33--------------\n");
				if (start_pipes != 0 && ret == 0)
				{
					//printf("2--------------\n");
					//printf("hello from docha1\n");
					dup2(fd[1], 1);
					close(fd[0]);
					//printf("hello from docha2\n");
					bsophia_function(start_pipes, untils);
					close(fd[1]);
				}
				else
				{
					//printf("3--------------\n");
					dup2(fd[0], 0);
					close(fd[1]);
					wait(0);
					close(fd[0]);
				}
				//printf("4--------------\n");
				dup2(tmpin, 0);
				dup2(tmpout, 1);
				//printf("4--------------\n");
				close(tmpout);
				close(tmpin);
				start_pipes = 0;
				start = start->next;
			}
			//printf("fsddf-->com = %s\n", start->command);
			ft_lstadd_back_parser(&start_pipes, ft_lstnew_parser(start->command, 0));
			start = start->next;
		}
		//ft_check_command(com->command);
		//printf("hello before change fd\n");
		dup2(tmpin2, 0);
		dup2(tmpout2, 1);
		//printf("command\n");

		if (start_pipes != 0)
		{
			redirect_check(start_pipes);
			//start_pipes->redir_right = com->redir_right;
			// if (start_pipes->redir_right)
			// 	fdout = open(start_pipes->redir_right, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			// else
			// 	fdout = dup(tmpout);
			// // com = start_pipes;
			// while (com) // echo pl | echo hgfda123 | echo 456
			// {
			// 	printf("%s  dr = %s  right = %s left = %s ->%d\n", com->command, com->redir_double_right, com->redir_right, com->redir_left, i);
			// 	com = com->next;
			// }
			bsophia_function(start_pipes, untils);
		}
		dup2(tmpin, 0);
		dup2(tmpout, 1);
	}
	dup2(tmpin2, 0);
	dup2(tmpout2, 1);
	// while (com)
	// {
	// 	printf("%s  dr = %s  right = %s left = %s ->%d\n", com->command, com->redir_double_right, com->redir_right, com->redir_left, i);
	// 	com = com->next;
	// }

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
