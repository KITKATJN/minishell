#include "minishell.h"

static int	check_for_echo(int *i, t_command *list, t_untils *untils)
{
	*i = 1;
	if (!list->next)
	{
		write(1, "\n", 1);
		return (1);
	}
	list = list->next;
	untils->status = 0;
	if ((!(ft_strcmp(list->command, "-n"))))
	{
		*i = 0;
		list = list->next;
	}
	return (0);
}

static void	echo_2(t_command *list, t_untils *untils)
{
	int		i;
	char	*line;
	char	*tmp;

	line = NULL;
	if (check_for_echo(&i, list, untils))
		return ;
	if (i == 0)
		list = list->next;
	list = list->next;
	while (list)
	{
		tmp = line;
		line = ft_strjoin_line(line, list->command);
		ft_free(tmp);
		if (ft_lstsize_2(list) != 1)
		{
			tmp = line;
			line = ft_strjoin_line(line, " ");
			ft_free(tmp);
		}
		list = list->next;
	}
	f_echo(line, i);
	ft_free(line);
}

static void	other_command(t_command *list, t_untils *untils)
{
	if (!(ft_strcmp(list->command, "unset")))
	{
		while (list->next)
		{
			list = list->next;
			untils->env = f_unset_line(untils->env, list->command, untils);
		}
	}
	if (!ft_strcmp(list->command, "exit"))
		ft_exit(list, untils);
}

void	bsophia_function(t_command *list, t_untils *untils)
{
	int	i;

	i = 0;
	if (!check_redir(list, 2, untils))
		return ;
	while (list->command[i])
	{
		list->command[i] = ft_tolower(list->command[i]);
		i++;
	}
	if (!(ft_strcmp(list->command, "echo")))
		echo_2(list, untils);
	untils->status = 0;
	if (!(ft_strcmp(list->command, "pwd")))
		get_pwd();
	if (!(ft_strcmp(list->command, "cd")))
		f_cd(list, untils);
	if (!(ft_strcmp(list->command, "env")))
		print_env(untils->env);
	if (!(ft_strcmp(list->command, "export")))
		execute_export(untils, list);
	other_command(list, untils);
	check_redir(list, 1, untils);
}
