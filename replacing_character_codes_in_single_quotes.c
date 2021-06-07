#include "minishell.h"

t_parser *replacing_character_codes_in_single_quotes(t_parser *start)
{
	t_parser *current;

	current = start;
	while (current)
	{
		//printf("lllllllllllllllllllll\n");
		if (current->special == 2)
		{
			current = current->next;
			if (current == 0)
				break ;
			while(current != 0 && current->special != 2 && current->back != 0 && current->back->special != 3)
			{
				//printf("hello %c\n", current->symbol[0]);
				current = current->next;
			}
			current = current->next;
			if (current == 0)
				break ;
			//printf("last -> %c next -> %c\n", current->symbol[0], current->next->symbol[0]);
		}
		//printf("+++++++++++++!%c! %d %d %d %p\n", current->symbol[0], current->symbol[0] == '\'' , current->special != 0 , current->back != 0, current->back);
		//if (current->back != 0)
			//printf("+++++++++++++!%c! %d %d %d %d\n", current->symbol[0], current->symbol[0] == '\'' , current->special != 0 , current->back != 0, current->back->special);
		if (current->symbol[0] == '\'' && current->special != 0 &&
			current->back != 0 && current->back->special != 3)//все что в обычных ковычках меняем на простые символы, которые ничего не значат
		{
			//printf("2*****************************\n");
			current = current->next;
			if (current == 0)
				break ;
			//printf("*****************************1\n");
			while (current->special != 1)
			{
				current->special = 0;
				current = current->next;
			}
		}
		//printf("////////////////////\n");
		current = current->next;
	}
	return (start);
}
