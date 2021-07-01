/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:12:51 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/05 16:00:02 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *scr, size_t n)
{
	size_t	i;
	char	*dest;
	char	*ssrc;

	if (dst == NULL && scr == NULL)
		return (NULL);
	i = 0;
	dest = (char *)dst;
	ssrc = (char *)scr;
	while (i < n)
	{
		dest[i] = ssrc[i];
		i++;
	}
	return (dest);
}
