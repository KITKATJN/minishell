#include "minishell.h"

static void	remove_paired_quotes3_3(t_rpq *rpq)
{
	if (rpq->current->symbol[0] == '\"' && rpq->current->next->symbol[0]
		== '\"' && rpq->current->back != 0 && rpq->current->back->special != 3)
	{
		rpq->tmp3 = rpq->current;
		while (rpq->tmp3)
		{
			if (rpq->tmp3->symbol[0] == '\'')
				rpq->num_quotes++;
			rpq->tmp3 = rpq->tmp3->back;
		}
		if (rpq->num_quotes % 2 == 0)
		{
			rpq->tmp = rpq->current->next;
			rpq->tmp2 = rpq->current->back;
			delete_current_parser2(rpq->current);
			delete_current_parser2(rpq->tmp);
			rpq->current = rpq->tmp2;
		}
	}
}

static void	remove_paired_quotes2_2(t_rpq *rpq)
{
	rpq->num_quotes = 0;
	if (rpq->current->symbol[0] == '\'' && rpq->current->next->symbol[0] == '\''
		&& rpq->current->back != 0 && rpq->current->back->special != 3)
	{
		rpq->tmp3 = rpq->current;
		while (rpq->tmp3)
		{
			if (rpq->tmp3->symbol[0] == '\"')
				rpq->num_quotes++;
			rpq->tmp3 = rpq->tmp3->back;
		}
		if (rpq->num_quotes % 2 == 0)
		{
			rpq->tmp = rpq->current->next;
			rpq->tmp2 = rpq->current->back;
			delete_current_parser2(rpq->current);
			delete_current_parser2(rpq->tmp);
			rpq->current = rpq->tmp2;
		}
	}
}

t_parser	*remove_paired_quotes(t_parser	*start)
{
	t_rpq	rpq;

	rpq.current = start;
	while (rpq.current->next)
	{
		remove_paired_quotes2_2(&rpq);
		remove_paired_quotes3_3(&rpq);
		rpq.current = rpq.current->next;
		if (rpq.current == 0)
			break ;
	}
	return (start);
}
