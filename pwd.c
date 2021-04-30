#include "minishell.h"

void get_pwd() //пока принимю строку, но скорее всего нужно принимать будет структуру и смотреть пайпы и редиректы тоже
{
	char *line;
	char *pwd;

	line = NULL;
	pwd = getcwd(line, 0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(line);
}
