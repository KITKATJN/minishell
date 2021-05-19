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
				printf("----->%c\n", start->command[i]);
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

void bsopia_func(t_command *com, int i, t_untils *untils)
{
	ft_check_command(com->command);
	ft_paste_env(com);
	// printf("command\n");
	bsophia_function(com, untils);

	while (com)
	{
		printf("%s operation ---->%d\n", com->command, i);
		com = com->next;
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
