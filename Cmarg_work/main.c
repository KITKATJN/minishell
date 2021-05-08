#include "head.h"

void ft_paste_env(t_command *list_of_command)
{
	t_command	*start;
	char		*start_command;
	char		*env;
	char		*value_env;
	int			i;

	start = list_of_command;
	while (start)
	{
		i = 0;
		while (start->command[i] != '\0')
		{
			if (start->command[i] == '$')
			{
				start_command = ft_substr(start->command, 0, i);
				env = ft_substr(start->command, i + 1, ft_strlen(start->command) - i + 1);
				if (getenv(env) == 0)
				{
					free(start_command);
					free(env);
					break ;
				}
				value_env = ft_strdup(getenv(env));
				free(env);
				free(start->command);
				start->command = ft_strjoin(start_command, value_env);
				free(start_command);
				free(value_env);
				break ;
			}
			i++;
		}
		start = start->next;
	}

}

void bsopia_func(t_command *com, int i)
{
	ft_check_command(com->command);
	ft_paste_env(com);
	while (com)
	{
		printf("%s operation ---->%d\n", com->command, i);
		com = com->next;
	}

}

int main(int argc, char** argv)
{
	t_command	*start;
	t_command	*current_command;

	start = 0;
	//start = parser_into_list("echo  -n     'y   sdf jghmj' \"f d!!!fs;ds\"  h    ff;vx sdf ft        mkk");
	start = parser_into_list("echo  -n $r rgdfg HELLO$PATH 'hgf';\" fsd; hjghj;;\"  ry rt $bf; trhur ;cat;  echo 'echo'\"hello\"");
	if (start->flag != 0 && !ft_strncmp("error", start->flag, ft_strlen("error")))
	{
		ft_perror(start->command);
	}
	pars_to_command(start);
	parse_add_semicolon_to_end(start);
	current_command = start;

	int i =1;
	t_command *new_start = 0;
	t_command *new_command;
	while (current_command)
	{
		if (current_command->command[0] == ';')
		{
			bsopia_func(new_start, i++);
			new_start = 0;
			current_command = current_command->next;
			if (current_command == 0)
				break ;
		}
		//printf("1---------------------------------------\n");
		new_command = ft_lstnew_parser(ft_strdup(current_command->command), 0);
		//printf("2---------------------------------------\n");
		ft_lstadd_back_parser(&new_start, new_command);
		//printf("3---------------------------------------\n");
		current_command = current_command->next;
	}
	if (new_start)
	{
		//printf("OMG\n");
		bsopia_func(new_start, i++);
		new_start = 0;
	}
	return 0;
}
