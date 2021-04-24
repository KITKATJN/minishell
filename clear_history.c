#include "minishell.h"

void clear_history(t_history **history)
{
	t_history *tmp;
	t_history *tmp2;

	tmp = *history;


	while(tmp)
	{
		printf("cont = !%s!\n", tmp->content);
		if (tmp->content == NULL)
		{
			tmp2 = tmp->back;
			tmp->back->next = 0;
			tmp->back = 0;
			*history = tmp2;
		}
		tmp = tmp->back;
	}
}
