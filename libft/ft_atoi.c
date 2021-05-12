/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:56:13 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/10 19:43:59 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int s)
{
	if ((s == ' ' || s == '\v' || s == '\t' || s == '\f'
		|| s == '\n' || s == '\r') && s != '\0')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *s)
{
	int		i;
	int		minus;
	int		cif;

	i = 0;
	minus = 1;
	cif = 0;
	while (1 == ft_isspace(s[i]) && s[i] != '\0')
		i++;
	if (s[i] == '-')
		minus = -1;
	if ((s[i] == '+' || s[i] == '-') && s[i] != '\0')
		i++;
	while (s[i] >= '0' && s[i] <= '9' && s[i] != '\0')
	{
		cif = (cif * 10) + (s[i] - 48) * minus;
		i++;
		if (cif < 0 && minus > 0)
			return (-1);
		if (cif > 0 && minus < 0)
			return (0);
	}
	return (cif);
}
