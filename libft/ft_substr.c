/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:03:45 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/09 20:52:02 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s) + 1)
		len = ft_strlen(s) + 1;
	if (ft_strlen(s) <= start)
	{
		result = ft_calloc(1, 1);
		return (result);
	}
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	while (s[start] != '\0' && len > 0)
	{
		result[i] = s[start];
		i++;
		start++;
		len--;
	}
	result[i] = '\0';
	return (result);
}
