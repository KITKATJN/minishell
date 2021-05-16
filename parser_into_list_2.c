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


t_parser	parser_into_list_2(char *str)
{
	t_parser	*start;
	t_parser	*current;
	char		*c;
	int			i;

	i = 0;
	start = 0;
	while (i < ft_strlen(str))
	{
		c = malloc(sizeof(char) * 2);
		ft_bzero(c, 2);
		c[0] = str[i];
		if (c[0] == '\\')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 3));
		else if (c[0] == '\"')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 2));
		else if (c[0] == '\'')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 1));
		else if (c[0] == '?')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 4));
		else if (c[0] == '$')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 5));
		else if (c[0] == ' ')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, -1));
		else
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 7));
		i++;
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

	//printf("1---------------\n");
	//printf_list(start);
	current = start;
	while (current)
	{
		if (current->symbol[0] == '\'')//все что в обычных ковычках меняем на простые символы, которые ничего не значат
		{
			current = current->next;
			while (current->symbol[0] != '\'')
			{
				current->special = 0;
				current = current->next;
			}
		}
		current = current->next;
	}


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
	//printf("3---------------\n");
	printf_list(start);

	current = start;
	t_parser *env_command;
	t_parser *head;
	char	*str_env;
	char	*tmp_env;
	int		i_env;
	int		iter;
	while (current->next)
	{
		printf("6--------\n");
		if (current->symbol[0] == '$' && current->special != 0)
		{
			i_env = 1;
			env_command = current;
			current = current->next;
			printf("5--------\n");
			while (current && current->special != 0 && current->special != -1 && current->special != 5 && current->special != 2)
			{
				i_env++;
				current = current->next;
			}
			printf("env %d\n", i_env);

			tmp_env = malloc(sizeof(char*) * i_env + 1);
			ft_bzero(tmp_env, i_env + 1);
			current = env_command;
			iter = 0;
			while (iter < i_env)
			{
				tmp_env[iter] = current->symbol[0];
				current = current->next;
				iter++;
			}
			printf("tmp_env %s\n", tmp_env);

			current = env_command;
			free(current->symbol);
			current->symbol = tmp_env;
			current = current->next;
			iter = 1;
			printf("1--------\n");
			while (iter < i_env)
			{
				head = current->back;
				delete_current_parser2(current);
				current = head;
				printf("2--------\n");
				current = current->next;
				iter++;
			}
			printf("3--------\n");
			current = env_command;
		}
		if (!current->next)
			break ;
		printf("7--------\n");
		current = current->next;
		printf("8--------\n");
	}

	printf("4--------\n");
	printf_list(start);
}
