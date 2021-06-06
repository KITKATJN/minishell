#include "minishell.h"

void	printf_list(t_parser *current)
{
	int i = 0;

	printf("----------------------------------------------------------------------------\n");
	while (current)
	{
		if (current->special_array == 0)
			printf("!%s! %d %p\n", current->symbol, current->special, current->back);
		else
		{
			printf("!%s! %d ->array", current->symbol, current->special);
			while (i < ft_strlen(current->symbol))
			{
				printf(" %d", current->special_array[i]);
				i++;
			}
			printf("\n");
			i = 0;
		}
		current = current->next;
		/* code */
	}
}

void	printf_command_list(t_command *current)
{
	printf("----------------------------------------------------------------------------\n");
	while (current)
	{
		printf("command = !%s! \n", current->command);
		current = current->next;
		/* code */
	}
}

t_command	*parser_into_list_2(char *str1, t_untils *untils)
{
	t_parser	*current;
	t_parser	*start;
	int			i;
	char 		*str;


	//printf("-------------->!%s!\n", str1);
	if (str1 == 0 || str1[0] == '\0')
		return (0);

	if (str1[0] == '\n')
		return(0);
	i = 0;
	int _flag = 0;
	if (str1[ft_strlen(str1) - 1] == '>' || str1[ft_strlen(str1) - 1] == '<')
		return (ft_lstnew_parser("syntax error near unexpected token `\\n'", 0));
	while (i < ft_strlen(str1))
	{
		if (str1[i] == '\"' || str1[i] == '\'')
			_flag++;
		if (str1[i] == ';' && _flag % 2 == 0)
		{
			i++;
			if (i >= ft_strlen(str1))
				break ;
			while (str1[i] == ' ')
				i++;
			if (i < ft_strlen(str1) && str1[i] == ';')
				return (ft_lstnew_parser("syntax error near unexpected token `;;'", 0));
		}
		if (str1[i] == '	')
		{
			return (ft_lstnew_parser("syntax error near unexpected token `	'", 0));
		}
		i++;
	}

	// if (_flag % 2 != 0)
	// {
	// 	return (ft_lstnew_parser(ft_strdup("error with quotes _==--_"), 0));
	// }

	i = 0;
	_flag = 0;
	while (i < ft_strlen(str1))
	{
		if (str1[i] == '\"' || str1[i] == '\'')
			_flag++;
		if (str1[i] == '|' && _flag % 2 == 0)
		{
			i++;
			if (i >= ft_strlen(str1))
				break ;
			while (str1[i] == ' ')
				i++;
			if (i < ft_strlen(str1) && str1[i] == '|')
			{
				i++;
				if (i >= ft_strlen(str1))
					break ;
				while (str1[i] == ' ')
					i++;
				if (i < ft_strlen(str1) && str1[i] == '|')
					return (ft_lstnew_parser("syntax error near unexpected token `|'", 0));
			}
		}
		i++;
	}

	str = ft_strdup(str1);
	//printf("--2------------>!%s!\n", str1);
	start = assigning_code_to_elements(str);
	//printf("fds %s\n", start->symbol);
	current = start;
	char u;
	while (current)
	{
		if (current->symbol[0] == '\\' && current->next == 0)
		{
			u = ' ';
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(&u), -1, 0));
		}
		current = current->next;
	}
	//printf_list(start);
	start = remove_paired_quotes(start);


	//printf("134---------------\n");
	//printf_list(start);
	start = replacing_character_codes_in_single_quotes(start);
	//printf("1349999999---------------\n");
	//printf_list(start);
	//printf("1---------------\n");
	current = start;
	t_parser *next;
	while (current->next)
	{
		if (current->special == 5)
		{
			if (current->next != 0 && current->next->symbol[0] == '\\')
				current->special = 0;
		}
		if (current->symbol[0] == '\\' && current->special != 0 && current->next->special != 7)
		{
			if (current->back == 0)
				start = current->next;
			next = current->next;
			delete_current_parser2(current);
			next->special = 0;
		}
		current = current->next;
	}
	//printf_list(start);
	//printf("1.5----------------------\n");

	current = start;
	int		count = 0;
	int		count_double = 0;
	while (current)
	{
		if (current->symbol[0] == '\'' && current->special != 0 && count_double % 2 == 0)//если ковычек не четное число то выходим с error
		{
			count++;
		}
		if (current->symbol[0] == '\"' && current->special != 0 && count % 2 == 0)//если ковычек не четное число то выходим с нулем
		{
			count_double++;
		}
		current = current->next;
	}
	if (count % 2 != 0 || count_double % 2 != 0)
	{
		return (ft_lstnew_parser(ft_strdup("error with quotes"), 0));
	}
	//printf("2---------------\n");
	//printf_list(start);
	//printf("2---------------\n");
	//printf_list(start);

	//printf("3---------------\n");
	//printf_list(start);

	current = start;
	while (current)
	{
		if (current->special == 2)//для замены пробелы на значащий в двойных ковычках
		{
			current = current->next;
			if (current == 0)
				break ;
			while (current->special != 2)
			{
				if (current->special == -1)
					current->special = 0;
				current = current->next;
			}
		}
		current = current->next;
	}

	//printf_list(start);

	//printf("4------------------------\n");
	current = start;
	t_parser *new_start;
	t_parser *list_of_command;
	new_start = start;
	int		*special_array;
	*str = 0;
	i = 0;
	int j = 0;
	list_of_command = 0;
	while (current)
	{
		if (current->special != -1)
			i++;
		if ((current->special == -1 || current->next == 0))
		{
			str = malloc(sizeof(char*) * i + 1);
			ft_bzero(str, i + 1);
			special_array = malloc(sizeof(int*) * i + 1);
			ft_bzero(special_array, i + 1);
			i = 0;
			while (new_start != current)
			{
				//printf("1------------------------\n");
				str[i] = new_start->symbol[0];
				special_array[i] = new_start->special;
				new_start = new_start->next;
				i++;
			}
			if (current->next == 0 && current->special != -1)
			{
				str[i] = new_start->symbol[0];
				special_array[i] = new_start->special;
			}
			ft_lstadd_back_parser2(&list_of_command, ft_lstnew_parser2(str, 0, special_array));
			i = 0;
			//printf("2------------------------%d\n", special_array[0]);
			if (new_start != 0)
				new_start = new_start->next;
		}
		current = current->next;
	}
	//printf_list(list_of_command);

	//printf("5------------------------\n");
 //надо удалять первоначчальный список
	while (start)
	{
		current = start->next;
		delete_current_parser2(start);
		start = current;
	}

	current = list_of_command->next;
	//printf_list(current);
	t_parser *temporary;
	while (current)
	{
		if (current->symbol[0] == '\0')
		{
			temporary = current;
			current = current->next;
			delete_current_parser2(temporary);
			continue ;
		}
		current = current->next;
	}
	//printf("5.5------------------------\n");

	// current = list_of_command;
	// if (current->symbol[0] == '\0')
	// 	{
	// 		temporary = current;
	// 		current = current->next;
	// 		delete_current_parser2(temporary);
	// 		list_of_command = current;
	// 	}
	//printf_list(current);
	while (current)
	{
		//printf("6.6.6------------------------%s\n", current->symbol);
		if (current->symbol[0] == '>' || current->symbol[0] == '<') //  проверяю, чтобы после каждого редиректа что-то было
		{
			//printf("gfdshkjbgfjkdsjkfgsf------------->%c\n",current->next->symbol[0] );
			if (current->next && (current->next->symbol[0] == '>' || current->next->symbol[0] == '<' || current->next->symbol[0] == ' ' || current->next->symbol[0] == ';'))
				return (ft_lstnew_parser("syntax error near unexpected token `>' or '<' or '>>'", 0));
		}
		//printf("5.5.5------------------------\n");
		current = current->next;
	}
	//printf_list(list_of_command);

	//printf("6------------------------\n");
	//printf("4------------------\n");
	t_command *commands;
	commands = 0;
	current = list_of_command;
	int i_env;
	int j_env;
	char *env_tmp;
	char *string_before_doolar;
	char *command_tmp;
	char *end_command;
	char *str_from_my_env;
	int i_for_str_before_dollar;
	//printf_list(current);
	while (current)
	{
		i_env = 0;
		end_command = malloc(1);
		end_command[0] = '\0';
		//printf("2-=========================== %d %s\n", current->special_array[i_env], current->symbol);
		string_before_doolar = malloc(sizeof(char*) * ft_strlen(current->symbol) + 1);
		ft_bzero(string_before_doolar, ft_strlen(current->symbol) + 1);
		i_for_str_before_dollar = 0;
		while (i_env < ft_strlen(current->symbol))
		{
			//printf("1/*/*/*/*/*/*/*/*/*/**/**/*\n");
			if (current->special_array[i_env] == 5)
			{
				env_tmp = malloc(sizeof(char*) * (ft_strlen(current->symbol) - i_env) + 1);
				ft_bzero(env_tmp, ft_strlen(current->symbol) - i_env + 1);
				j_env = i_env + 1;
				i = 0;
				while (j_env < ft_strlen(current->symbol))
				{
					if (current->special_array[j_env] == 0 || current->special_array[j_env] == 5 || current->special_array[j_env] == 3 || (current->special_array[0] == 2 && current->special_array[j_env] == 2))
						break;
					env_tmp[j_env - i_env - 1] = current->symbol[j_env];
					j_env++;
				}
				str_from_my_env = my_get_env(env_tmp, untils->env);
				//printf("str from my get env %s\n", str_from_my_env);
				if (str_from_my_env == 0)
				{
					command_tmp = malloc(1);
					command_tmp[0] = '\0';
				}
				else
				{
					//printf("olala !%s!\n", my_get_env(env_tmp, untils->env));
					command_tmp = str_from_my_env;// ft_strjoin(getenv(env_tmp), current->symbol + j_env);
				}
				free(env_tmp);
				//printf("command_tmp1 = %s\n", command_tmp);
				//if (i_env > 0)
				//	command_tmp = ft_strjoin(ft_substr(current->symbol, 0 , i_env), command_tmp);
				//printf("command_tmp2 = %s\n", command_tmp);
				end_command = ft_strjoin(end_command, string_before_doolar);
				//printf("end_command1 = %s\n", end_command);
				end_command = ft_strjoin(end_command, command_tmp);
				free(command_tmp);
				//printf("end_command2 = %s\n", end_command);
				//printf("env_tmp = %s %s \n", env_tmp, command_tmp);
				i_env = j_env;
				ft_bzero(string_before_doolar, ft_strlen(current->symbol) + 1);
				i_for_str_before_dollar = 0;
				//printf("cyter ====->%c %d\n", current->symbol[i_env], i_env);
				continue ;
			}
			if (i_env < ft_strlen(current->symbol))
			{
				string_before_doolar[i_for_str_before_dollar] = current->symbol[i_env];
			}
			//printf("2/*/*/*/*/*/*/*/*/*/**/**/*\n");
			i_for_str_before_dollar++;
			i_env++;
		}
		//printf("string_before_doolar = %s | %s\n", string_before_doolar, end_command);
		end_command = ft_strjoin(end_command, string_before_doolar);
		free(string_before_doolar);
		//printf("34/*/*/*/*/*/*/*/*/*/**/**/*\n");
		if (end_command[0] != '\0' || current->symbol[0] == '$')
			current->symbol = end_command;
		//printf("current->symb = %s\n", current->symbol);
		//printf("35/*/*/*/*/*/*/*/*/*/**/**/*\n");
		if (current->special_array[0] == 9)
		{
			//printf("1-----------------\n");
			//printf_command_list(commands);
			bsopia_func(commands, 2, untils);
			if (current->next == 0)
				break ;
			current = current->next;
			commands = 0;
		}
		//printf("3/*/*/*/*/*/*/*/*/*/**/**/*\n");
		ft_lstadd_back_parser(&commands, ft_lstnew_parser(ft_strdup(current->symbol), 0));
		//printf("4/*/*/*/*/*/*/*/*/*/**/**/*\n");
		current = current->next;
	}
	bsopia_func(commands, 0, untils);
	//printf("2-----------------\n");
	//printf_command_list(commands);
	//printf_command_list(commands);
	// current = list_of_command;
	// t_parser *temporary2;
	// while (current)
	// {
	// 	temporary2 = current;
	// 	current = current->next;
	// 	delete_current_parser2(temporary2);
	// 	current = current->next;
	// }
	//printf("7------------------------\n");
	return (commands);
}
