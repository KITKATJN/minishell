#include "minishell.h"

t_command	*parser_into_list(char *str1, t_untils *untils)
{
	t_parser	*current;
	t_parser	*start;
	int			i;
	char 		*str;


	//printf("-------------->!%s!\n", str1);
	if (str1 == 0 || str1[0] == '\0' || str1[0] == '\n')
		return (0);
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
	start = escaping_characters(start);
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
	start = change_escape_code_in_double_quotes(start);
	t_parser *list_of_command;
	list_of_command = assigning_symbols_to_command(start);

	current = list_of_command;
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
	// if (ft_strcmp(ft_check_command(list_of_command->symbol), "error") == 0)
	// {
	// 	ft_lstclear_parser2(&list_of_command);
	// 	return (ft_lstnew_parser("error: command not found", 0));
	// }
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
	char *tmp;
	//printf_list(current);
	while (current)
	{
		i_env = 0;
		end_command = ft_calloc(1, 1);
		string_before_doolar = ft_calloc(ft_strlen(current->symbol) + 1, ft_strlen(current->symbol) + 1);
		i_for_str_before_dollar = 0;
		while (i_env < ft_strlen(current->symbol))
		{
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
				if (str_from_my_env == 0)
					command_tmp = ft_calloc(1, 1);
				else
					command_tmp = str_from_my_env;// ft_strjoin(getenv(env_tmp), current->symbol + j_env);
				ft_free(env_tmp);
				end_command = ft_strjoin(end_command, string_before_doolar);
				end_command = ft_strjoin(end_command, command_tmp);
				ft_free(command_tmp);
				i_env = j_env;
				ft_bzero(string_before_doolar, ft_strlen(current->symbol) + 1);
				i_for_str_before_dollar = 0;
				continue ;
			}
			if (i_env < ft_strlen(current->symbol))
				string_before_doolar[i_for_str_before_dollar] = current->symbol[i_env];
			i_for_str_before_dollar++;
			i_env++;
		}
		tmp = end_command;
		end_command = ft_strjoin(end_command, string_before_doolar);
		ft_free(tmp);
		ft_free(string_before_doolar);
		if (end_command[0] != '\0' || current->symbol[0] == '$')
		{
			ft_free(current->symbol);
			current->symbol = end_command;
		}
		if (current->special_array[0] == 9)
		{
			bsopia_func(commands, 2, untils);
			ft_lstclear_command(&commands);
			if (current->next == 0)
				break ;
			current = current->next;
		}
		ft_lstadd_back_parser(&commands, ft_lstnew_parser(ft_strdup(current->symbol), 0));
		current = current->next;
	}
	bsopia_func(commands, 0, untils);
	ft_lstclear_command(&commands);
	ft_lstclear_parser2(&list_of_command);
	return (commands);
}
