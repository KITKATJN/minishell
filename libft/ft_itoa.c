/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:57:54 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/10 19:44:45 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_int(int n)
{
	int		count;

	count = 0;
	if (n == 0)
		return (0);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static int	abss(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*f;
	int		i;

	i = count_int(n);
	if (n == 0)
	{
		f = malloc(2);
		f[0] = '0';
		f[1] = '\0';
		return (f);
	}
	f = malloc(count_int(n) + 1);
	if (!f)
		return (NULL);
	if (n < 0)
		f[0] = '-';
	f[i--] = '\0';
	while (abss(n))
	{
		f[i--] = abss(n % 10) + '0';
		n = n / 10;
	}
	return (f);
}
