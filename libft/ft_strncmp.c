/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:54:39 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/05 14:18:55 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	size_t			j;
	unsigned char	*s_s1;
	unsigned char	*s_s2;

	s_s1 = (unsigned char *)s1;
	s_s2 = (unsigned char *)s2;
	i = 0;
	j = 0;
	while (j < n && ((s_s1[i] && s_s2[i]) != '\0'))
	{
		if (s_s1[i] == s_s2[i] && (s_s1[i] != '\0' && s_s2[i] != '\0'))
		{
			i++;
			j++;
		}
		else if (s_s1[i] != s_s2[i])
			return (s_s1[i] - s_s2[i]);
	}
	if (s_s1[i] == '\0' && s_s2[i] != '\0' && j < n)
		return (-1);
	else if (s_s1[i] != '\0' && s_s2[i] == '\0' && j < n)
		return (1);
	return (0);
}
