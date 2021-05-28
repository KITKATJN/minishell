#include "minishell.h"

t_parser	*ft_lstnew_parser2(char *symbol, int special, int *special_array)
{
	t_parser	*lst;

	lst = (t_parser*)malloc(sizeof(t_parser));
	if (lst)
	{
		lst->symbol = symbol;
		lst->special = special;
		lst->next = 0;
		lst->back = 0;
		lst->special_array = special_array;
	}
	return (lst);
}

void	ft_lstadd_back_parser2(t_parser **lst, t_parser *new)
{
	t_parser	*list;

	if (lst && new)
	{
		if (*lst == 0)
			*lst = new;
		else
		{
			list = *lst;
			while (list->next)
				list = list->next;
			list->next = new;
			new->back = list;
		}
	}
}

void	delete_current_parser2(t_parser *current)
{
	t_parser	*back;
	t_parser	*next;

	if (current != 0)
	{
		next = current->next;
		back = current->back;
		if (next != 0)
			next->back = back;
		if (back != 0)
			back->next = next;
	//	if (current->symbol != 0)
		//	free(current->symbol);
		free (current);
	}
}

void	printf_list(t_parser *current)
{
	int i = 0;

	printf("----------------------------------------------------------------------------\n");
	while (current)
	{
		if (current->special_array == 0)
			printf("!%s! %d\n", current->symbol, current->special);
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
	t_parser	*start;
	t_parser	*current;
	char		*c;
	int			i;
	int			count_1;
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
			if (i + 1 < ft_strlen(str1) && str1[i + 1] == ';')
				return (ft_lstnew_parser("syntax error near unexpected token `;;'", 0));
		}
		if (str1[i] == '	')
		{
			return (ft_lstnew_parser("syntax error near unexpected token `	'", 0));
		}
		i++;
	}
	str = ft_strdup(str1);
	//printf("--2------------>!%s!\n", str1);	
	count_1 = 0;
	i = 0;
	start = 0;
	char *r;
	int flag_delete_probel = 0;
	r = malloc(sizeof(char) * 2);
	ft_bzero(r, 2);
	r[0] = ' ';
	while (i < ft_strlen(str))
	{
		if (str[i] == ' ' && !flag_delete_probel)
		{
			i++;
			continue ;
		}
		c = malloc(sizeof(char) * 2);
		ft_bzero(c, 2);
		c[0] = str[i];
		if (c[0] == '\\')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 3, 0));
		else if (c[0] == '\"')
		{
			count_1++;
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 2, 0));
		}
		else if (c[0] == '\'')
		{
			count_1++;
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 1, 0));
		}
		else if (c[0] == '?')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 4, 0));
		else if (c[0] == '$')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 5, 0));
		else if (c[0] == ' ')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, -1, 0));
		else if (c[0] == ';' && count_1 % 2 == 0)
		{
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1, 0));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 9, 0));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1, 0));
		}
		else if (c[0] == '>' && count_1 % 2 == 0)
		{
			if (i + 1 < ft_strlen(str1) && str[i + 1] == '>')
			{
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 29, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 29, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1, 0));
				i++;
			}
			else
			{
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 19, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1, 0));
			}
		}
		else if (c[0] == '<' && count_1 % 2 == 0)
		{
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 18, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1, 0));
		}
		else
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 7, 0));
		flag_delete_probel = 1;
		i++;
		//free(c);
	}

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

	current = start;
	t_parser	*tmp;
	t_parser	*tmp2;
	t_parser	*tmp3;
	int			num_quotes;
	while (current->next)
	{
		num_quotes = 0;

	//printf("1---456789------------\n");
	//printf("1---------------%s\n", current->symbol);
		if (current->symbol[0] == '\'' && current->next->symbol[0] == '\'')//удаляю все парные ковычки. baby я хулиган как  Simpson Bart
		{
			tmp3 = current;
			//printf("1+---------------\n");
			while (tmp3)
			{
				if(tmp3->symbol[0] == '\"') //здесь и ниже я удаляю кавычки стоящие ввместе, но не удаляю ковычки стоящие вместе в других ковычках
					num_quotes++;
				tmp3 = tmp3->back;
			}

	//printf("1&---------------\n");
			if (num_quotes % 2 == 0)
			{
				tmp = current->next;
				tmp2 = current->back;
				delete_current_parser2(current);
				delete_current_parser2(tmp);
				current = tmp2;
			}

	//printf("1*---------------\n");
		}
		if (current->symbol[0] == '\"' && current->next->symbol[0] == '\"')//удаляю все парные ковычки. baby я хулиган как  Simpson Bart
		{
			tmp3 = current;
			while (tmp3)
			{
				if(tmp3->symbol[0] == '\'')
					num_quotes++;
				tmp3 = tmp3->back;
			}
			if (num_quotes % 2 == 0)
			{
				tmp = current->next;
				tmp2 = current->back;
				delete_current_parser2(current);
				delete_current_parser2(tmp);
				current = tmp2;
			}
		}

	//printf("1---dfghj------------\n");

		current = current->next;
		if (current == 0)
			break ;
	}

	//printf("134---------------\n");
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
		if (current->symbol[0] == '\\' && current->special != 0)
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
		printf("error with quotes %d\n", count);
		return (ft_lstnew_parser(ft_strdup("error with quotes"), 0));
	}
	//printf("2---------------\n");
	//printf_list(start);
	current = start;
	while (current)
	{
		if (current->special == 2)
		{
			current = current->next;
			while(current->special != 2)
				current = current->next;
		}
		if (current->symbol[0] == '\'' && current->special != 0)//все что в обычных ковычках меняем на простые символы, которые ничего не значат
		{
			current = current->next;
			if (current == 0)
				break ;
			while (current->special != 1)
			{
				current->special = 0;
				current = current->next;
			}
		}
		current = current->next;
	}
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

 //надо удалять первоначчальный список
	while (start)
	{
		current = start->next;
		delete_current_parser2(start);
		start = current;
	}

	current = list_of_command;
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

	current = list_of_command;
	while (current)
	{
		if (current->symbol[0] == '>' || current->symbol[0] == '<') //  проверяю, чтобы после каждого редиректа что-то было
		{
			//printf("gfdshkjbgfjkdsjkfgsf------------->%c\n",current->next->symbol[0] );
			if (current->next && (current->next->symbol[0] == '>' || current->next->symbol[0] == '<' || current->next->symbol[0] == ' ' || current->next->symbol[0] == ';'))
				return (ft_lstnew_parser("syntax error near unexpected token `>' or '<' or '>>'", 0));
		}
		current = current->next;
	}
	//printf_list(list_of_command);

	//printf("4------------------\n");
	t_command *commands;
	commands = 0;
	current = list_of_command;
	int i_env;
	int j_env;
	char *env_tmp;
	char *string_before_doolar;
	char *command_tmp;
	char *end_command = malloc(1);
	end_command[0] = '\0';
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
				//printf("%d === %ld !%s!\n", j_env ,ft_strlen(current->symbol), string_before_doolar);
				while (j_env < ft_strlen(current->symbol))
				{
					if (current->special_array[j_env] == 0 || current->special_array[j_env] == 5)
						break;
					env_tmp[j_env - i_env - 1] = current->symbol[j_env];
					//printf("*** %c  %d %c\n", env_tmp[j_env - i_env - 1],j_env - i_env - 1 , current->symbol[j_env]);
					j_env++;
				}
				//printf("env_tmp = %s\n", env_tmp);
				if (getenv(env_tmp) == 0)
					command_tmp = 0;
				else
					command_tmp = ft_strdup(getenv(env_tmp));// ft_strjoin(getenv(env_tmp), current->symbol + j_env);
				//printf("command_tmp1 = %s\n", command_tmp);
				if (command_tmp == 0)
				{
					command_tmp = malloc(1);
					command_tmp[0] = '\0';
				}
				//if (i_env > 0)
				//	command_tmp = ft_strjoin(ft_substr(current->symbol, 0 , i_env), command_tmp);
				//printf("command_tmp2 = %s\n", command_tmp);
				end_command = ft_strjoin(end_command, string_before_doolar);
				//printf("end_command1 = %s\n", end_command);
				end_command = ft_strjoin(end_command, command_tmp);
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
		//printf("string_before_doolar = %s\n", string_before_doolar);
		end_command = ft_strjoin(end_command, string_before_doolar);
		//printf("34/*/*/*/*/*/*/*/*/*/**/**/*\n");
		if (end_command[0] != '\0')
			current->symbol = end_command;
		//printf("35/*/*/*/*/*/*/*/*/*/**/**/*\n");
		if (current->special_array[0] == 9)
		{
			//printf("1-----------------\n");
			//printf_command_list(commands);
			bsopia_func(commands, 0, untils);
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
	return (commands);
}
