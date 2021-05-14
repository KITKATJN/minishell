#include "minishell.h"

int		delete_spaces(char **arr_of_command, char *argv, int i, char delimiter)
{
	int	j;
	int	k;
	char	*str;

	j = i + 1;
	while (j < ft_strlen(argv))
	{
		if (arr_of_command[j][0] == delimiter)
			break;
		j++;
	}
	str = malloc(sizeof(char) * (j - i + 2));
	ft_bzero(str, (j - i + 2));
	k = 0;
	while (i + k < j + 1)
	{
		str[k] = arr_of_command[i + k][0];
		//printf("arr========%c\n", arr_of_command[i + k][0]);
		arr_of_command[i + k][0] = '\0';
		k++;
	}
	free(arr_of_command[i]);
	arr_of_command[i] = 0;
	arr_of_command[i] = str;
	return (i + k);

	//free(arr_of_command[i + 1]);
	//printf("->%d\n", j + 1);
	// arr_of_command[i + 1] = ft_substr(argv, i, j - i + 1);
	// arr_of_command[i][0] = '\0';
	// i += 2;
	// while (i < j + 1)
	// {
	// 	arr_of_command[i][0] = '\0';
	// 	i++;
	// // }
	// return (i);
}
