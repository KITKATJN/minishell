#include "minishell.h"

char *my_get_env(char *str, char **env)
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	result = NULL;
	while (env[j] != NULL)
	{
		i = 0;
		if (ft_strnstr(env[j], str, ft_strlen(str)) != 0 && env[j][ft_strlen(str)] == '=')
		{
			//printf("->>%s\n", ft_strdup(&env[j][ft_strlen(str) + 1]));
			return (ft_strdup(&env[j][ft_strlen(str) + 1]));
		}
		// while (str[i] != '\0')
		// {
		// 	printf("! %s ! %s !\n", &str[i], &env[j][i]);
		// 	if (!(ft_strcmp(&str[i], &env[j][i])) && env[j][++i] == '=')
		// 	{
		// 		printf("4\n");
		// 		i++;
		// 	}
		// 	else if (env[j][i] == '=' && str[i] == '\0')
		// 	{
		// 		printf("2222222\n");
		// 		result = ft_strdup_b(&env[j][i]);
		// 		printf("result = %s\n", result);
		// 		return (result);
		// 	}
		// 	else
		// 		break;
		// 	// i++;
		// }
		// if (env[j][i] == '=' && str[i] == '\0')
		// {
		 	//printf("2222222->%s = %c\n",ft_strnstr(env[j], str, ft_strlen(str)) , env[j][ft_strlen(str)]);
		// 	result = ft_strdup_b(&env[j][i]);
		// 	printf("result = %s\n", result);
		// 	return (result);
		// }
		j++;
	}
//	printf("123123123121\n");
	// printf("%s\n", env[j]);
	// if (env[j][i] == '=' && str[i] == '\0')
	// {
	// 	result = ft_strdup_b(&env[j][i]);
	// 	// printf("result = %s\n", result);
	// 	return (result);
	// }
	return (NULL);
}
