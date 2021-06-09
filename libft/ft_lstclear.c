/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:46:12 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/11 15:00:11 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*temp;

	head = *lst;
	if (!(*lst))
		return ;
	while (head)
	{
		temp = head->next;
		del(head->content);
		free(head);
		head = temp;
	}
	*lst = NULL;
}
