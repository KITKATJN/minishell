#include "minishell.h"

void	parse_add_semicolon_to_end(t_command *start)
{
	t_command	*curr_command;
	t_command	*new_command;
	char		*command;

	curr_command = start;
	while (curr_command)
	{
		if (ft_strlen(curr_command->command) > 1
			&& curr_command->command
			[ft_strlen(curr_command->command) - 1] == ';')
		{
			new_command = ft_lstnew_parser(ft_strdup(";"), 0);
			command = ft_substr(curr_command->command,
					0, ft_strlen(curr_command->command) - 1);
			ft_free(curr_command->command);
			curr_command->command = command;
			new_command->next = curr_command->next;
			new_command->back = curr_command;
			curr_command->next = new_command;
			if (curr_command->next != 0)
				curr_command->next->back = new_command;
		}
		curr_command = curr_command->next;
	}
}
