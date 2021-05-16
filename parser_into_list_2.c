#include "minishell.h"

t_parser	*ft_lstnew_parser2(char *symbol, int special)
{
	t_parser	*lst;

	lst = (t_parser*)malloc(sizeof(t_parser));
	if (lst)
	{
		lst->symbol = symbol;
		lst->special = special;
		lst->next = 0;
		lst->back = 0;
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
		free(current->symbol);
		free (current);
	}
}

void	printf_list(t_parser *current)
{
	printf("----------------------------------------------------------------------------\n");
	while (current)
	{
		printf("!%s! %d\n", current->symbol, current->special);
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

t_parser	*parser_into_list_2(char *str, t_untils *untils)
{
	t_parser	*start;
	t_parser	*current;
	char		*c;
	int			i;
	int			count_1;

	count_1 = 0;
	i = 0;
	start = 0;
	char r = ' ';
	while (i < ft_strlen(str))
	{
		c = malloc(sizeof(char) * 2);
		ft_bzero(c, 2);
		c[0] = str[i];
		if (c[0] == '\\')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 3));
		else if (c[0] == '\"')
		{
			count_1++;
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 2));
		}
		else if (c[0] == '\'')
		{
			count_1++;
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 1));
		}
		else if (c[0] == '?')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 4));
		else if (c[0] == '$')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 5));
		else if (c[0] == ' ')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, -1));
		else if (c[0] == ';' && count_1 % 2 == 0)
		{
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(&r, -1));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 9));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(&r, -1));
		}
		else
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 7));
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
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(&u), -1));
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
		if (current->symbol[0] == '\'' && current->next->symbol[0] == '\'')//удаляю все парные ковычки. baby я хулиган как  Simpson Bart
		{
			tmp3 = current;
			while (tmp3)
			{
				if(tmp3->symbol[0] == '\"') //здесь и ниже я удаляю кавычки стоящие ввместе, но не удаляю ковычки стоящие вместе в других ковычках
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
		current = current->next;
	}

	//printf_list(start);
	//printf("1---------------\n");
	current = start;
	t_parser *next;
	while (current->next)
	{
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
	while (current)
	{
		if (current->symbol[0] == '\'' && current->special != 0)//если ковычек не четное число то выходим с error
		{
			count++;
		}
		if (current->symbol[0] == '\"' && current->special != 0)//если ковычек не четное число то выходим с нулем
		{
			count++;
		}
		current = current->next;
	}
	if (count % 2 != 0)
	{
		printf("error with quotes %d\n", count);
		return (ft_lstnew_parser2(ft_strdup("error with quotes"), 0));
	}
	//printf("2---------------\n");
	//printf_list(start);
	current = start;
	while (current)
	{
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
	//printf("3.5---------------\n");
	//printf_list(start);
	// current = start;
	// t_parser *env_command;
	// t_parser *head;
	// char	*str_env;
	// char	*tmp_env;
	// int		i_env;
	// int		iter;
	// while (current->next)
	// {
	// 	//printf("6--------\n");
	// 	if (current->symbol[0] == '$' && current->special != 0)
	// 	{
	// 		i_env = 1;
	// 		env_command = current;
	// 		current = current->next;
	// 		//printf("5--------\n");
	// 		while (current && current->special != 0 && current->special != -1 && current->special != 5 && current->special != 2)
	// 		{
	// 			i_env++;
	// 			current = current->next;
	// 		}
	// 		//printf("env %d\n", i_env);

	// 		tmp_env = malloc(sizeof(char*) * i_env + 1);
	// 		ft_bzero(tmp_env, i_env + 1);
	// 		current = env_command;
	// 		iter = 0;
	// 		while (iter < i_env)
	// 		{
	// 			tmp_env[iter] = current->symbol[0];
	// 			current = current->next;
	// 			iter++;
	// 		}
	// 		//printf("tmp_env %s\n", tmp_env);

	// 		current = env_command;
	// 		free(current->symbol);
	// 		current->symbol = tmp_env;
	// 		current = current->next;
	// 		iter = 1;
	// 		//printf("1--------\n");
	// 		while (iter < i_env)
	// 		{
	// 			head = current->back;
	// 			delete_current_parser2(current);
	// 			current = head;
	// 			//printf("2--------\n");
	// 			current = current->next;
	// 			iter++;
	// 		}
	// 		//printf("3--------\n");
	// 		current = env_command;
	// 	}
	// 	if (!current->next)
	// 		break ;
	// 	//printf("7--------\n");
	// 	current = current->next;
	// 	//printf("8--------\n");
	// }

	//printf("4--------\n");
	//printf_list(start);

	current = start;
	t_parser	*new_start;
	t_parser	*new_start2;
	t_parser	*new_head;
	t_command	*command;
	int		comm_iterator;
	char	*str_command;
	char	*final_command;
	int		l;
	char	*env;
	int	l_env;
	//int		length_command;
	command = 0;
	comm_iterator = 0;
	new_start = start;
	while (current)
	{
		if (current->special == 9)
		{
			if (command->command[0] == '\0')
				command = command->next;
			bsopia_func(command,1, untils);
			command = 0;
			current = current->next;
		}
		//printf("1------------------\n");
		if (current->special == 5)
		{
			new_start2 = current;
			l_env = 1;
			new_start2 = new_start2->next;
			//printf("56------------------\n");
			while(new_start2 != 0 && new_start2->special != 5 && new_start2->special != 0 && new_start2->special != -1)
			{
				l_env++;
				new_start2 = new_start2->next;
			}
			//printf("23------------------\n");
			env = malloc(sizeof(char*) * l_env + 1);
			ft_bzero(env, l_env + 1);
			new_start2 = current;
			l_env = 0;
			new_start2 = new_start2->next;
			while(new_start2 != 0 && new_start2->special != 5 && new_start2->special != 0 && new_start2->special != -1)
			{
				env[l_env] = new_start2->symbol[0];
				l_env++;
				new_start2 = new_start2->next;
			}
			//printf("873------------------\n");
			str_command = env;
			if (!getenv(env))
				env = ft_strdup(" ");
			else
				env = ft_strdup(getenv(env));
			free(str_command);
			//printf("env = %s !%s!\n", getenv(env), env);
			new_start2 = current;
			new_start2->symbol = env;
			while(new_start2->next != 0 && new_start2->next->special != 5 && new_start2->next->special != 0 && new_start2->next->special != -1)
			{
				delete_current_parser2(new_start2->next);
			}
			//printf("env = %s !%s!\n", getenv(env), env);
			//printf_list(start);
		}
		//printf("2------------------ %p\n", current);
		if (current->special == -1 || current->next == 0)
		{
			//printf("3------------------ \n");
			if (current->next == 0)
				comm_iterator++;
			//printf(" new start = !%s! iter = %d\n", new_start->symbol, comm_iterator);
			//printf("!%s! %d\n", current->symbol, current->special);
			str_command = malloc(sizeof(char*) * comm_iterator + 1);
			ft_bzero(str_command, comm_iterator + 1);
			l = 0;
			//length_command = 0;
			//printf("4------------------\n");
			while (l < comm_iterator)
			{
				//printf("5.5------------------%s\n", str_command);
				if (new_start == 0 || new_start->special == -1)
					break;
				str_command = ft_strjoin(str_command,new_start->symbol);
				l++;
				//printf("5------------------\n");
				new_start = new_start->next;
			}
			//printf("6------------------\n");
			ft_lstadd_back_parser(&command,ft_lstnew_parser(str_command, 0));
			//printf("str_command = !%s!\n", str_command);
			comm_iterator = -1;
			new_start = current->next;
		}
		comm_iterator += ft_strlen(current->symbol);
		current = current->next;
	}
	if (command)
	{
		if (command->command[0] == '\0')
			command = command->next;
		bsopia_func(command,2, untils);
	}
	//printf_command_list(command);
	//printf_list(start);
}
