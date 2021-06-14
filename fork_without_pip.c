#include "minishell.h"

int	fork_without_pip(t_command *com, t_untils *untils)
{
	t_command	*start;

	start = com;
	com = redirect_check(com, untils);
	if (com == 0)
		return (1);
	while (start)
	{
		start->command = replace_dollar_que_into_code(start->command, untils);
		start = start->next;
	}
	start = com;
	return (0);
}
