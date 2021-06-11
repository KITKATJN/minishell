#include "minishell.h"

static int compare_to_equal(char *s1, char *s2)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);  //подали уникальный ключ
		if (s1[i] == '=' && s2[i] == '=')
			return (1); //ключи одинаковые
		i++;
	}
	return (0);
}

int check_name(char *str)
{
	int i;

	i = 0;
	if (!(ft_isalpha(str[0])) && str[0] != '_')
		return (1);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!(ft_isalpha(str[i])) && (!(ft_isdigit(str[i]))) 
			&& str[i] != '_' && str[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

static char **export_add_2(char **cp_env, char *str, t_untils *untils, int i)
{
	char **new_env;

	new_env = (char**)malloc(i * sizeof(char*));
	i = 0;
	while(cp_env[i] != NULL)
	{
		new_env[i] = ft_strdup(cp_env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	i = 0;
	while(cp_env[i] != NULL)
		ft_free(cp_env[i++]);
	ft_free(cp_env);
	untils->env = new_env;
	return(new_env);
}

char **export_add(char **cp_env, char *str, t_untils *untils)
{
	int i;
	// char **new_env;
	int k;

	k = 0;
	i = 0;
	if (check_name(str))
	{
		printf("export: %s: not a valid identifier\n", str);
		untils->status = 1;
		return (cp_env);
	}
	while(cp_env[i] != NULL)
	{
		if (!ft_strcmp(cp_env[i], str)) //если подают ключ со значением которое уже есть то не будет записываться ничего
			return(cp_env);
		if (compare_to_equal(cp_env[i], str)) //если ключ существует то значение в нем заменится на новое;
		{
			ft_free(cp_env[i]);
			cp_env[i] = NULL;
			cp_env[i] = ft_strdup(str);
			return(cp_env);
		}
		i++;
	}
	i += 2;
	return (export_add_2(cp_env, str, untils, i));
	// new_env = (char**)malloc(i * sizeof(char*));
	// i = 0;
	// while(cp_env[i] != NULL)
	// {
	// 	new_env[i] = ft_strdup(cp_env[i]);
	// 	i++;
	// }
	// new_env[i++] = ft_strdup(str);
	// new_env[i] = NULL;
	// i = 0;
	// while(cp_env[i] != NULL)
	// 	ft_free(cp_env[i++]);
	// ft_free(cp_env);
	// untils->env = new_env;
	// return(new_env);
}
