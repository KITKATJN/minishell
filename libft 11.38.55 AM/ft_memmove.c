/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:36:45 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/11 12:31:47 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dd;
	unsigned char	*ss;

	dd = (unsigned char *)dst;
	ss = (unsigned char *)src;
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			dd[len] = ss[len];
		}
	}
	else
		ft_memcpy(dd, ss, len);
	return (dd);
}
