#include "minishell.h"

int check_buildin(char *str)
{
	if (!(ft_strcmp(str, "echo")) || !(ft_strcmp(str, "env")) || !(ft_strcmp(str, "export")) || !(ft_strcmp(str, "pwd")) || !(ft_strcmp(str, "cd")) || !(ft_strcmp(str, "unset")))
		return (0);
	return (1);
}

char *find_path(t_untils *untils)
{
	int i;
	char *str;

	str = NULL;
	i = 0;
	while(untils->env[i] != NULL)
	{
		if (untils->env[i][0] == 'P' && untils->env[i][1] == 'A' && untils->env[i][2] == 'T' && untils->env[i][3] == 'H' && untils->env[i][4] == '=')
		{
			str = ft_strdup_b(&untils->env[i][5]);
			return (str);
		}
		i++;
	}
	return (NULL);
}