#include "head.h"

void	delete_tcommand(t_command *command)
{
	if (command != 0)
	{
		if (command->command != 0)
			free(command->command);
		if (command->flag != 0)
			free(command->flag);
		if (command->argument != 0)
			free(command->argument);
	}
}
