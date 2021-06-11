#include "minishell.h"

void	ft_lstclear_command(t_command **lst)
{
	t_command	*head;
	t_command	*temp;

	head = *lst;
	if (!(*lst))
		return ;
	while (head)
	{
		temp = head->next;
		delete_current_parser_for_command_list(head);
		head = temp;
	}
	*lst = NULL;
}

t_command	*ft_lstnew_parser(void *command, void *flag)
{
	t_command	*lst;

	lst = (t_command *)malloc(sizeof(t_command));
	if (lst)
	{
		lst->command = command;
		lst->flag = flag;
		lst->next = 0;
		lst->argument = 0;
		lst->redir_double_right = NULL;
		lst->redir_left = NULL;
		lst->redir_right = NULL;
		lst->error = 0;
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

void	delete_current_parser_for_command_list(t_command *current)
{
	t_command	*back;
	t_command	*next;

	if (current != 0)
	{
		ft_free(current->command);
		ft_free(current->redir_double_right);
		ft_free(current->redir_left);
		ft_free(current->redir_right);
		ft_free(current->flag);
		ft_free(current);
	}
}

void	delete_current_parser(t_command *current)
{
	t_command	*back;
	t_command	*next;

	if (current != 0)
	{
		next = current->next;
		back = current->back;
		if (next != 0)
			next->back = back;
		if (back != 0)
			back->next = next;
		ft_free(current->command);
		ft_free(current->redir_double_right);
		ft_free(current->redir_left);
		ft_free(current->redir_right);
		ft_free(current->flag);
		free (current);
	}
}
