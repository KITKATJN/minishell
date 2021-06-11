#include "minishell.h"

void	last(t_command *command, t_untils *untils, int error)
{
	printf("exit: too many arguments\n");
	ft_exit2(command, untils, EXIT_FAILURE);
}

void	check_name_exit(t_command *command, t_untils *untils, int error)
{
	if (command->next == 0)
	{
		error = untils->status;
		ft_exit2(command, untils, error);
	}
}

void	check_name_exit_2(t_command *command, t_untils *untils, int error)
{
	int	i;

	i = -1;
	while (command->next->command[++i] != 0)
	{
		if (ft_isalpha(command->next->command[i]))
		{
			printf("exit\n%s: numeric argument required\n",
				command->next->command);
			ft_exit2(command, untils, 255);
		}
	}
}
