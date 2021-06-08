#include "minishell.h"

void	printf_list(t_parser *current)
{
	int i = 0;

	printf("----------------------------------------------------------------------------\n");
	while (current)
	{
		if (current->special_array == 0)
			printf("!%s! %d %p\n", current->symbol, current->special, current->back);
		else
		{
			printf("!%s! %d ->array", current->symbol, current->special);
			while (i < ft_strlen(current->symbol))
			{
				printf(" %d", current->special_array[i]);
				i++;
			}
			printf("\n");
			i = 0;
		}
		current = current->next;
		/* code */
	}
}

void	printf_command_list(t_command *current)
{
	printf("----------------------------------------------------------------------------\n");
	while (current)
	{
		printf("command = !%s! \n", current->command);
		current = current->next;
		/* code */
	}
}
