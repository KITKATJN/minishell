#include "minishell.h"

int		ft_strcmp(char *str, char *str1)
{
	int	i;

	i = 0;
	while (str[i] && str1[i])
	{
		if (str[i] == str1[i])
			i++;
		else
			return (str[i] - str1[i]);
	}
	if (str[i] == '\0' && str1[i] != '\0')
		return (-1);
	if (str[i] != '\0' && str1[i] == '\0')
		return (1);
	return (0);
}
