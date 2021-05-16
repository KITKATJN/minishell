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
		next->back = back;
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
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 0));
		i++;
	}
	current = start;
	while (current)
	{
		printf("!%s! %d\n", current->symbol, current->special);
		current = current->next;
		/* code */
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
			next = current->next;
			delete_current_parser2(current);
			next->special = 0;
		}
		current = current->next;
		/* code */
	}
	printf_list(start);
}
