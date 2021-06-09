/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:43:38 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/10 19:45:42 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		abss(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

static int		count_intt(int n)
{
	int			count;

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

void			ft_putnbr_fd(int n, int fd)
{
	char		bb[13];
	int			i;

	if (n == 0)
		write(fd, "0", 1);
	i = count_intt(n);
	if (n < 0)
		bb[0] = '-';
	bb[i--] = '\0';
	while (abss(n))
	{
		bb[i--] = abss(n % 10) + '0';
		n = n / 10;
	}
	i = 0;
	while (bb[i] != '\0')
	{
		write(fd, &bb[i], 1);
		i++;
	}
}
