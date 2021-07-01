/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:28:40 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/06 17:25:31 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack,
	const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	j = ft_strlen(needle);
	i = 0;
	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	if (haystack == NULL && needle == NULL)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && len >= ft_strlen(needle))
	{
		if (needle[0] == haystack[i])
			if (0 == ft_strncmp(&haystack[i], needle, j))
				return ((char *)&haystack[i]);
		len--;
		i++;
	}
	return (NULL);
}
