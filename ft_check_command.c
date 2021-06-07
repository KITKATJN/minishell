#include "minishell.h"

char	*ft_check_command(char *command)
{
	//printf("1----------------tmp = %s\ncommand--->%s\n", tmp, command);
	if (command[0] == 'e')
	{
		if (!ft_strncmp(command, "echo", 4))
			return ("echo");
		if (!ft_strncmp(command, "env", 3))
			return ("env");
		if (!ft_strncmp(command, "exit", 4))
			return ("exit");
		if (!ft_strncmp(command, "export", 6))
			return ("export");
		ft_putstr_fd("command \"", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("\" not found\n", 2);
		return ("error");
	}
	if (!ft_strncmp(command, "cd", ft_strlen(command)))
		return ("cd");
	if (!ft_strncmp(command, "pwd", ft_strlen(command)))
		return ("pwd");
	if (!ft_strncmp(command, "unset", ft_strlen(command)))
		return ("unset");
	// ft_putstr_fd("command \"", 2);
	// ft_putstr_fd(command, 2);
	// ft_putstr_fd("\" not found\n", 2);
	return ("error");
}
