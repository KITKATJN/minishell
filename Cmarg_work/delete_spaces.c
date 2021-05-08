#include "head.h"

int		delete_spaces(char **arr_of_command, char *argv, int i, char delimiter)
{
	int	j;

	j = i + 1;
	while (j < ft_strlen(argv))
	{
		if (arr_of_command[j][0] == delimiter)
			break;
		j++;
	}
	free(arr_of_command[i + 1]);
	printf("->%d\n", j + 1);
	arr_of_command[i + 1] = ft_substr(argv, i, j - i + 1);
	arr_of_command[i][0] = '\0';
	i += 2;
	while (i < j + 1)
	{
		arr_of_command[i][0] = '\0';
		i++;
	}
	return (i);
}
