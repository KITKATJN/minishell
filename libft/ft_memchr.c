/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:21:43 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/10 13:50:08 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	point;

	p = (unsigned char *)s;
	point = (unsigned char)c;
	i = 0;
	while (*p != '\0' && i < n)
	{
		if (*p == point)
			return (p);
		i++;
		p++;
	}
	if (*p == point && i < n)
		return (p);
	return (NULL);
}
