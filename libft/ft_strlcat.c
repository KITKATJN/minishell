/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:26:32 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/03 20:19:10 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			scr_len;
	size_t			dst_len;
	size_t			i;

	i = 0;
	scr_len = ft_strlen(src);
	while (*dst && i < dstsize)
	{
		dst++;
		i++;
	}
	dst_len = i;
	if (dstsize != 0)
		while (*src && i < dstsize - 1)
		{
			*dst = *src;
			dst++;
			src++;
			i++;
		}
	if (i < dstsize)
		*dst = '\0';
	return (dst_len + scr_len);
}
