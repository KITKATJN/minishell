#include "minishell.h"

void	ft_free(void *p)
{
	if (p != 0)
	{
		free(p);
		p = 0;
	}
}
