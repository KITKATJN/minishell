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
	int _flag_pipes = 0;
	if (str1[ft_strlen(str1) - 1] == '>' || str1[ft_strlen(str1) - 1] == '<')
	{
		untils->status = 258;
		return (ft_lstnew_parser("syntax error near unexpected token `\\n'", 0));
	}
	while (i < ft_strlen(str1))
	{
		if (str1[i] == '|' && _flag_pipes == 0)
		{
			untils->status = 258;
			return (ft_lstnew_parser("syntax error near unexpected token '|'", 0));
		}
		if (str1[i] != '|' && str1[i] != ' ')
			_flag_pipes = 1;
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
			{
				untils->status = 258;
				return (ft_lstnew_parser("syntax error near unexpected token `;;'", 0));
			}
		}
		if (str1[i] == '	')
		{
			untils->status = 258;
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
				{
					untils->status = 258;
					return (ft_lstnew_parser("syntax error near unexpected token `|'", 0));
				}
			}
		}
		i++;
	}

	str = ft_strdup(str1);
	//printf("--2------------>!%s!\n", str1);
	start = assigning_code_to_elements(str);
	ft_free(str);
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
	start = remove_paired_quotes(start);
	printf_list(start);
	start = replacing_character_codes_in_single_quotes(start);
	printf_list(start);
	start = escaping_characters(start);

	current = start;
	int		count = 0;
	int		count_double = 0;
	printf_list(start);
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
		ft_lstclear_parser2(&start);
		return (ft_lstnew_parser("error with quotes", 0));
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
			if (current->next && (current->next->symbol[0] == '>' || current->next->symbol[0] == '<' || current->next->symbol[0] == ' ' || current->next->symbol[0] == ';' || current->next->symbol[0] == '|'))
				return (ft_lstnew_parser("syntax error near unexpected token `>' or '<' or '>>'", 0));
		}
		//printf("5.5.5------------------------\n");
		current = current->next;
	}
	//printf_list(list_of_command);
	if (list_of_command->symbol[0] == '\0')
	{
		current = list_of_command;
		list_of_command = list_of_command->next;
		delete_current_parser2(current);
	}

	return (command_transmission_to_bsopia(list_of_command, untils));
}
