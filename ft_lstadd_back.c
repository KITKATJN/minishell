#include "minishell.h"

void	ft_lstadd_back(t_history **lst, t_history *new)
{
	t_history	*temp;

	temp = *lst;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		new->back = temp;
		temp->next = new;
		*lst = temp->next;
	}
	else
		*lst = new;
}
