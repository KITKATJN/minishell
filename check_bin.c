#include "minishell.h"

int check_bin(char *str)
{
	if (str[0] == '/')
		return (1);
	return (0);
}
