/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:15:49 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/03 17:53:04 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ss;

	ss = (char *)s;
	i = 0;
	while (ss[i] != '\0')
		i++;
	if (ss[i] == c)
		return (&ss[i]);
	i = i - 1;
	while (i != -1)
	{
		if (ss[i] == c)
			return (&ss[i]);
		i--;
	}
	return (NULL);
}
