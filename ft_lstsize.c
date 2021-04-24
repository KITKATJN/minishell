#include "minishell.h"

int		ft_lstsize(t_history *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->back;
	}
	return (i);
}
