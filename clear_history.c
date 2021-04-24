#include "minishell.h"

void clear_history(t_history **history)
{
	t_history *tmp;
	t_history *tmp2;

	tmp = *history;


	while(tmp && ft_lstsize(*history) >= 1)
	{
		//printf("cont = !%s!\n", tmp->content);
		if (tmp->content == NULL)
		{
			tmp2 = tmp->back;
			if (tmp->back)
			{
				tmp->back->next = 0;
				tmp->back = 0;
			}
			free(tmp);
			tmp = 0;
			*history = tmp2;
			break ;
		}
		tmp = tmp->back;
	}
}
