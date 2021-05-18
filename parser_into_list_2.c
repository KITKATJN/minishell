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
	//	if (current->symbol != 0)
		//	free(current->symbol);
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

t_command	*parser_into_list_2(char *str, t_untils *untils)
{
	t_parser	*start;
	t_parser	*current;
	char		*c;
	int			i;
	int			count_1;

	//printf("-------------->!%s!\n", str);
	if (str == 0 || str[0] == '\0')
		return (0);
	if (str[0] == '\n')
		return(0);
	count_1 = 0;
	i = 0;
	start = 0;
	char *r;
	r = malloc(sizeof(char) * 2);
	ft_bzero(r, 2);
	r[0] = ' ';
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
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 9));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(r, -1));
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
		return (ft_lstnew_parser(ft_strdup("error with quotes"), 0));
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

	//printf_list(start);

	current = start;
	t_parser *new_start;
	t_parser *list_of_command;
	new_start = start;
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
			i = 0;
			while (new_start != current)
			{
				//printf("1------------------------\n");
				str[i] = new_start->symbol[0];
				new_start = new_start->next;
				i++;
			}
			if (current->next == 0 && current->special != -1)
				str[i] = new_start->symbol[0];
			ft_lstadd_back_parser2(&list_of_command, ft_lstnew_parser2(str, 0));
			i = 0;
			//printf("2------------------------\n");
			if (new_start != 0)
				new_start = new_start->next;
		}
		current = current->next;
	}
//	printf_list(list_of_command);

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
//	printf_list(list_of_command);

	t_command *commands;
	commands = 0;
	current = list_of_command;
	while (current)
	{
		ft_lstadd_back_parser(&commands, ft_lstnew_parser(ft_strdup(current->symbol), 0));
		current = current->next;
	}

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
