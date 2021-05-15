#include "minishell.h"

static int quotes(char *str, int i, char delimetr)
{
	while (str[i] != delimetr && str[i] != 0)
	{
		i++;
	}
	return (i);
}

static char *couple_for_quotes(char *str, int i, char delimetr)
{
	char *new_str;

	if (str[i] == 0)
	{
		new_str = malloc(sizeof(char *) * ft_strlen(str) + 2);
		i = 0;
		while (str[i])
		{
			new_str[i] = str[i];
		i++;
		}
		new_str[i] = delimetr;
		new_str[i + 1] = '\0';
		return (new_str);
	}
	return (0);
}

char *add_quotes(char *str)
{
	int		i;
	char	*new_str;

	if (!str)
		return (0);
	i = 0;
	while(str[i])
	{
		if (str[i] == '\'')
		{
			i = quotes(str, i + 1, '\'');
			new_str = couple_for_quotes(str, i, '\'');
			if (new_str != 0)
				return (new_str);
		}
		if (str[i] == '\"')
		{
			i = quotes(str, i + 1, '\"');
			new_str = couple_for_quotes(str, i, '\"');
			if (new_str != 0)
				return (new_str);
		}
		i++;
	}
	return (0);
}
