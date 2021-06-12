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
