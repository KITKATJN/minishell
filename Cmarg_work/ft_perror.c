#include "head.h"

void	ft_perror(char *error)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 1);
	exit(-1);
}
