#include "minishell.h"

int f_echo(char *str, int i) //пока принимю строку, но скорее всего нужно принимать будет структуру и смотреть еще флаг -n (пайпы и редиректы тоже)
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
