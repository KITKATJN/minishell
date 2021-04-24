#include "minishell.h"

t_history		*ft_lstnew(void *content)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	if (!new)
		return (NULL);
	if (new)
	{
		new->content = content;
		new->next = 0;
		new->back = 0;
		return (new);
	}
	else
		return (new);
}
