#include "minishell.h"

int f_cd(t_command *list)
{
	int i;

	list = list->next;
	i = chdir(list->command);
	return (i);
}
