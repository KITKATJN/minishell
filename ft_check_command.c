#include "minishell.h"

char	*ft_check_command(char *command)
{
	char	*tmp;
	int		i;
	int		i_double_quotes;
	int		i_alone_quotes;
	int		j;

	tmp = malloc(sizeof(char) * ft_strlen(command));
	ft_bzero(tmp, ft_strlen(command));
	i = 0;
	j = 0;
	i_alone_quotes = 0;
	i_double_quotes = 0;
	//printf("command[i] =------------> %s\n", command);
	//printf("1----------------\n");
	while (command[i] != '\0')
	{
		if (command[i + 1] != '\0')
		{
			if (command[i] != '\\' && command[i + 1] != '\\')
			{
				tmp[j] = command[i];
				j++;
				i++;
				continue ;
			}
		}
		else if (command[i] == '\\' && command[i + 1] == '\0')
		{
			tmp[j] = command[i];
			break ;
		}
		if (command[i] != '\\' && command[i] != '\'' && command[i] != '\"')
		{
			tmp[j] = command[i];
			j++;
		}
		//printf("command[i] = %c\n", command[i]);
		i++;
	}
	//printf("1----------------tmp = %s\ncommand--->%s\n", tmp, command);
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
		ft_putstr_fd("command \"", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("\" not found\n", 2);
		return ("error");
	}
	if (!ft_strncmp(command, "cd", ft_strlen("cd")))
		return ("cd");
	if (!ft_strncmp(command, "pwd", ft_strlen("pwd")))
		return ("pwd");
	if (!ft_strncmp(command, "unset", ft_strlen("unset")))
		return ("unset");
	ft_putstr_fd("command \"", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\" not found\n", 2);
	return ("error");
}
