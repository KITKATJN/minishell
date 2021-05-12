/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsophia <bsophia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:45:01 by bsophia           #+#    #+#             */
/*   Updated: 2020/11/11 14:59:02 by bsophia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_sep(char const *ss, char c)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (ss[i] != '\0')
	{
		if (ss[i] != c)
		{
			j++;
			while (ss[i] != c && ss[i] != '\0')
				i++;
		}
		if (ss[i] == '\0')
			break ;
		i++;
	}
	return (j);
}

static char		*word(char const *s_1, char c, int *i)
{
	char		*word_1;
	int			b;
	int			kk;

	b = *i;
	kk = 0;
	while (s_1[*i] != '\0')
	{
		if (s_1[*i] == c)
			break ;
		(*i)++;
		kk++;
	}
	word_1 = malloc(kk + 1);
	if (!word_1)
		return (NULL);
	*i = b;
	b = 0;
	while (s_1[*i] != c && s_1[*i] != '\0')
		word_1[b++] = s_1[(*i)++];
	word_1[b] = '\0';
	return (word_1);
}

static char		**free_result(char **result, int j)
{
	while (j)
	{
		j--;
		free(result[j]);
	}
	free(result);
	return (NULL);
}

char			**ft_split(const char *s, char c)
{
	char		**result;
	int			i;
	int			j;

	if (!s)
		return (NULL);
	i = count_sep(s, c);
	if (!(result = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			result[j++] = word(s, c, &i);
			if (!result[j - 1] && j != 0)
				return (free_result(result, j));
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}
