#include "minishell.h"

int f_cd(char *str)
{
	int i;

	i = chdir(str);
	return (i);
}
