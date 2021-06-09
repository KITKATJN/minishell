#include "minishell.h"

static  int    ft_atoi_long_long(const char *nptr)
{
	int      i;
	long long  j;
	int      minus;

	i = 0;
	j = 0;
	minus = 1;
	while (nptr[i] == ' ' || nptr[i] == ' ' || nptr[i] == '\n'
		|| nptr[i] == '\t' || nptr[i] == '\f' ||
		nptr[i] == '\r' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
		minus = (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		j = (j * 10) + (nptr[i] - 48);
		i++;
	}
	return ((int)(j * minus));
}

void      ft_exit(t_command *command, t_untils *untils)
{
	int      error;
	int      i;

	if (command->next == 0)
	{
		delete_current_parser_for_command_list(command);
		error = untils->status;
		delete_current_untils(untils);
		exit(error);
	}
	if (command->next->next == 0)
	{
		i = 0;
		while (command->next->command[i] != 0)
		{
			if (ft_isalpha(command->next->command[i]))
			{
				delete_current_parser_for_command_list(command);
				delete_current_untils(untils);
				exit(EXIT_NOT_FOUND);
			}
		i++;
		}
		delete_current_parser_for_command_list(command);
		delete_current_untils(untils);
		exit((unsigned char)ft_atoi(command->next->command));
	}
	delete_current_parser_for_command_list(command);
	delete_current_untils(untils);
	exit(EXIT_FAILURE);
}
