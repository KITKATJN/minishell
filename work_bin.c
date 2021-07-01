#include "minishell.h"

static int	get_number_arg(t_command *com)
{
	int	i;

	i = 0;
	while (com->command && com->command[i] != '\0')
		i++;
	while (com->command && com->command[i] != '/')
		i--;
	return (i);
}

static char	**get_argument(t_command *com, int i, int j)
{
	char		**argument;
	t_command	*save;

	save = com;
	while (com)
	{
		com = com->next;
		i++;
	}
	com = save;
	argument = (char **)malloc(sizeof(char *) * (i + 1));
	i = get_number_arg(com);
	argument[j] = ft_strdup_b(&com->command[i + 1]);
	j++;
	com = com->next;
	while (com)
	{
		argument[j++] = ft_strdup_b(com->command);
		com = com->next;
	}
	argument[j] = NULL;
	return (argument);
}

void	work_bin(t_command *com, t_untils *untils)
{
	int			i;
	char		**argument;
	t_command	*save;
	int			j;

	i = 0;
	j = 0;
	save = com;
	argument = 0;
	argument = get_argument(com, 0, 0);
	com = save;
	execve(com->command, argument, NULL);
	if (errno == 13)
	{
		printf("%s: is a directory\n", com->command);
		exit(126);
	}
	printf("%s: No such file or directory\n", com->command);
	exit (127);
}
