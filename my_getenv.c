#include "minishell.h"

char *my_get_env(char *str, char **env)
{
	int i;
	int j;
	char *result;
	char *tmp;

	i = 0;
	j = 0;
	result = NULL;
	//printf("get str -> %s env -> %s\n", str, env[0]);
	while (env[j] != NULL)
	{
		i = 0;
		tmp = ft_strdup(env[j]);
		result = ft_strnstr(tmp, str, ft_strlen(str));
		if (result != 0 && tmp[ft_strlen(str)] == '=')
		{
			// ft_free(result);
			result = ft_strdup(&tmp[ft_strlen(str) + 1]);
			ft_free(tmp);
			return (result);
		}
		ft_free(tmp);
		j++;
	}
	return (NULL);
}
