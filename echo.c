#include "minishell.h"

int	f_echo(char *str, int i)
{
	if (i == 1)
	{
		write(1, str, ft_strlen_b(str));
		write(1, "\n", 1);
	}
	if (i == 0)
		write(1, str, ft_strlen_b(str));
	return (0);
}
