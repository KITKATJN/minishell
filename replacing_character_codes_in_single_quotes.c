#include "minishell.h"

t_parser *replacing_character_codes_in_single_quotes(t_parser *start)
{
	t_parser *current;

	current = start;
	while (current)
	{
		if (current->special == 2)
		{
			current = current->next;
			if (current == 0)
				break ;
			while(current != 0 && current->special != 2 && current->back != 0 && current->back->special != 3)
			{
				current = current->next;
			}
			if (current == 0)
				break ;
			current = current->next;
			if (current == 0)
				break ;
		}
		if (current->symbol[0] == '\'' && current->special != 0 &&
			current->back != 0 && current->back->special != 3)//все что в обычных ковычках меняем на простые символы, которые ничего не значат
		{
			current = current->next;
			if (current == 0)
				break ;
			while (current != 0 && current->special != 1)
			{
				current->special = 0;
				current = current->next;
			}
		}
		if (current->symbol[0] == '\'' && current->special != 0 &&
			current->back == 0)//все что в обычных ковычках меняем на простые символы, которые ничего не значат
		{
			current = current->next;
			if (current == 0)
				break ;
			while (current != 0 && current->special != 1)
			{
				current->special = 0;
				current = current->next;
			}
		}
		if (current == 0)
			break ;
		current = current->next;
	}
	return (start);
}
