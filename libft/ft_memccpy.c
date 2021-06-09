/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:59:16 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/10 20:25:31 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*srrc;
	unsigned char	*dstt;
	unsigned char	cc;

	srrc = (unsigned char*)src;
	dstt = (unsigned char*)dst;
	cc = (unsigned char)c;
	while (n)
	{
		*dstt = *srrc;
		if (*dstt == cc)
			return (++dstt);
		srrc++;
		dstt++;
		n--;
	}
	return (NULL);
}
