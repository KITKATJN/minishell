#include "minishell.h"

static int compare_to_equal(char *s1, char *s2)
{
	int i;
	int flag;

	// s2 = ft_strjoin_line(s2, "=");
	i = 0;
	flag = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '=' && s2[i] == '\0')
			return (1);
		if (s1[i] != s2[i])
			return (0);  //подали уникальный ключ
		if (s1[i] == '=' && s2[i] == '\0')
			return (1); //ключи одинаковые
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
			return (1);
	return (0);
}

static int  check_name1(char *str) //сделать проверку что бы начиналось только с букв или же с _(как в экспорте)
{
	int i;

	i = 0; 
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char **f_unset_line(char **cp_env, char *str)
{
	char **new_env;
	int i;
	int flag;
	int k;

	i = 0;
	flag = 2;
	k = 0;
	if (!str)
		return (cp_env); //если пустой unset подают то возвращаем сразу наш входящий массив
	if (check_name1(str))
		return (cp_env);
	while(cp_env[i] != NULL)
	{
		if (compare_to_equal(cp_env[i], str)) //если нашли ключ кладем туда значение 55, так как в переменных окружения нельзя что бы 1 символ был цифрой то наше значение будет уникальным и не будет пересекаться
		{
			free(cp_env[i]);
			cp_env[i] = NULL;
			cp_env[i] = ft_strdup("55");
			flag = 1;
		}
		i++;
	}
	if (flag == 2) //если в нашем массиве не нашелся нужный ключ то удалять ничего не нужно, возвращаем текущий массив
		return (cp_env);
	new_env = (char**)malloc(i * sizeof(char*));
	i = 0;
	while (cp_env[i] != NULL)
	{
		if (strcmp(cp_env[i], "55")) //если это не 55 то копируем наши данные в новый массив
		{
			new_env[k] = ft_strdup(cp_env[i]);
			i++;
			k++;
		}
		else
			i++;
	}
	new_env[k] = NULL;
	i = 0;
	while(cp_env[i] != NULL)
		free(cp_env[i++]);
	free(cp_env);
	return (new_env);
}
