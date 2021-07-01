#include "minishell.h"

void	delete_tcommand(t_command *command)
{
	if (command != 0)
	{
		ft_free(command->command);
		ft_free(command->flag);
		ft_free(command->argument);
	}
}
