#include "head.h"

char	*ft_check_command(char *command)
{
	if (command[0] == 'e')
	{
		if (!ft_strncmp(command, "echo", ft_strlen("echo")))
			return ("echo");
		if (!ft_strncmp(command, "env", ft_strlen("env")))
			return ("env");
		if (!ft_strncmp(command, "exit", ft_strlen("exit")))
			return ("exit");
		if (!ft_strncmp(command, "export", ft_strlen("export")))
			return ("export");
		return ("err");
	}
	if (!ft_strncmp(command, "cd", ft_strlen("cd")))
		return ("cd");
	if (!ft_strncmp(command, "pwd", ft_strlen("pwd")))
		return ("pwd");
	if (!ft_strncmp(command, "unset", ft_strlen("unset")))
		return ("unset");
	ft_putstr_fd("command \"", 2);
	ft_putstr_fd(command, 2);
	ft_perror("\" not found");
}
