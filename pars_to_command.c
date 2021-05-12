#include "minishell.h"

void			pars_to_command(t_command *start)
{
	t_command	*curr_command;
	t_command	*new_command;
	char		*str;

	curr_command = start;
	str = 0;
	while (curr_command)
	{
		str = ft_strnstr(curr_command->command, ";", ft_strlen(curr_command->command) - 1);
		if ((str != 0) && curr_command->command[0] != '\'' && curr_command->command[0] != '\"')
		{
			new_command = ft_lstnew_parser(ft_substr(str, 1, ft_strlen(str)), 0);
			str = curr_command->command;
			curr_command->command = ft_substr(curr_command->command, 0, ft_strlen(curr_command->command) - ft_strlen(new_command->command));
			new_command->next = curr_command->next;
			if (curr_command->next != 0)
				curr_command->next->back = new_command;
			curr_command->next = new_command;
			new_command->back = curr_command;
			if (str != 0)
			{
				free(str);
				str = 0;
			}
		}
		curr_command = curr_command->next;
	}
}
