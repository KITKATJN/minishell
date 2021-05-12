#include "minishell.h"

t_command	*ft_lstnew_parser(void *command, void *flag)
{
	t_command	*lst;

	lst = (t_command*)malloc(sizeof(t_command));
	if (lst)
	{
		lst->command = command;
		lst->flag = flag;
		lst->next = 0;
		lst->argument = 0;
	}
	return (lst);
}

void	ft_lstadd_back_parser(t_command **lst, t_command *new)
{
	t_command	*list;

	if (lst && new)
	{
		if (*lst == 0)
			*lst = new;
		else
		{
			list = *lst;
			while (list->next)
				list = list->next;
			list->next = new;
			new->back = list;
		}
	}
}
