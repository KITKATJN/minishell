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
		if (current->special_array != 0)
		{
			free(current->special_array);
			current->special_array = 0;
		}
		free(current->symbol);
		current->symbol = 0;
		free(current);
	}
}
