/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:50:35 by bsophia           #+#    #+#             */
/*   Updated: 2021/05/15 18:34:33 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
