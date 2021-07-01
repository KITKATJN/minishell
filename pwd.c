#include "minishell.h"

void	get_pwd(void)
{
	char	*line;
	char	*pwd;

	line = NULL;
	pwd = getcwd(line, 0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	ft_free(line);
	ft_free(pwd);
}

int	check_spaces(char *str1)
{
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	while (i < ft_strlen(str1))
	{
		if (str1[i] != ' ')
			flag = 0;
		i++;
	}
	return (flag);
}
