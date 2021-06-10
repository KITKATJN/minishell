#include "minishell.h"

static char **get_argument(t_command *com)
{
	int i;
	char **argument;
	t_command *save;
	int j;

	save = com;
	i = 0;
	j = 0;
	while (com)
	{
		com = com->next;
		i++;
	}
	com = save;
	argument = ft_calloc(i + 1, i + 1);
	i = 0;
	while (com->command && com->command[i] != '\0')
		i++;
	while (com->command && com->command[i] != '/')
		i--;
	argument[j] = ft_strdup_b(&com->command[i + 1]);
	j++;
	com = com->next;
	while (com)
	{
		argument[j] = ft_strdup_b(com->command);
		j++;
		com = com->next;
	}
	argument[j] = NULL;
	return (argument);
}

void work_bin(t_command *com, t_untils *untils)
{
	int i;
	char **argument;
	t_command *save;
	int j;

	i = 0;
	save = com;
	argument = 0;
	argument = get_argument(com);
	com = save;
	j = 0;
	execve(com->command, argument, NULL);
	printf("! %s !\n", strerror(errno));
	printf("%s\n", com->command);
	exit (127);
}
