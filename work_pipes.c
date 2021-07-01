#include "minishell.h"

static void	execve_works_3(t_untils *untils, t_command *start)
{
	int			i;
	char		*commd;
	char		*command;

	i = -1;
	command = NULL;
	commd = ft_strjoin_line("/", untils->command_ex);
	if (!check_redir(start, 2, untils))
	{
		ft_free(commd);
		exit(1);
	}
	while (untils->bin[++i])
	{
		command = ft_strjoin_line(untils->bin[i], commd);
		execve(command, untils->arguments, untils->env);
		ft_free(command);
	}
	if (untils->bin[i] == NULL && ft_strcmp(untils->command_ex, "minishell")
		&& ft_strcmp(untils->command_ex, "./minishell")
		&& ft_strcmp(untils->command_ex, "$?"))
		exit(127);
	if (ft_strcmp(untils->command_ex, "$?"))
		printf("0 : command not found");
}

static void	execve_works_2(t_untils *untils, t_command *start)
{
	t_command	*save;
	int			i;

	save = start;
	untils->bin = ft_split(untils->path, ':');
	i = 0;
	while (start)
	{
		start = start->next;
		i++;
	}
	untils->arguments = (char **)malloc(sizeof(char *) * (i + 1));
	start = save;
	i = 0;
	while (start)
	{
		untils->arguments[i] = ft_strdup_b(start->command);
		start = start->next;
		i++;
	}
	untils->arguments[i] = NULL;
}

static void	execve_works(t_untils *untils, t_command *start)
{
	t_command	*save;
	char		*tmp;

	save = start;
	untils->command_ex = ft_strdup_b(start->command);
	if (check_bin(start->command))
	{
		if (!check_redir(start, 2, untils))
			exit(1);
		work_bin(start, untils);
	}
	tmp = find_path(untils);
	if (!(tmp) && !(check_bin(start->command)))
		exit(127);
	ft_free(tmp);
	untils->path = find_path(untils);
	if (!untils->path)
		exit(1);
}

int	work_pipes(t_untils *untils, t_command *start)
{
	t_command	*save;

	start = redirect_check(start, untils);
	if (start == 0)
		return (0);
	save = start;
	while (save)
	{
		save->command = replace_dollar_que_into_code(save->command, untils);
		save = save->next;
	}
	save = start;
	if (check_buildin(start->command))
	{
		execve_works(untils, start);
		execve_works_2(untils, start);
		execve_works_3(untils, start);
	}
	else
	{
		bsophia_function(save, untils);
		exit(0);
	}
	return (1);
}
