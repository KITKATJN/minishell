/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:34:20 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/10 19:48:22 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check(const char *sep, char character)
{
	int			j;

	j = 0;
	while (sep[j] != '\0')
	{
		if (sep[j] == character)
			return (1);
		j++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char		*result;
	int			i;
	int			j;
	int			k;

	i = 0;
	k = 0;
	if (!s1)
		return (NULL);
	j = ft_strlen(s1) - 1;
	while (1 == check(set, s1[i]) && s1[i] != '\0')
		if (s1[++i] == '\0')
		{
			result = ft_strdup("");
			return (result);
		}
	while (1 == check(set, s1[j]))
		j--;
	result = malloc((j - i) + 2);
	if (!result)
		return (NULL);
	while (i != j + 1)
		result[k++] = s1[i++];
	result[k] = '\0';
	return (result);
}
