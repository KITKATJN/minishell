#include "minishell.h"

static char	*find_home(t_untils *untils)
{
	int		i;
	char	*home;

	home = NULL;
	i = 0;
	while (untils->env[i] != NULL)
	{
		if (untils->env[i][0] == 'H' && untils->env[i][1] == 'O'
			&& untils->env[i][2] == 'M' && untils->env[i][3] == 'E'
			&& untils->env[i][4] == '=')
		{
			home = ft_strdup_b(&untils->env[i][5]);
			return (home);
		}
		i++;
	}
	return (NULL);
}

static int	cd_other(t_untils *untils, t_command *list)
{
	char	*pwd;
	char	*tmp;
	char	*line;

	line = NULL;
	untils->home = find_home(untils);
	if (!untils->home)
	{
		printf("cd : HOME not set\n");
		untils->status = 1;
		return (1);
	}
	pwd = getcwd(line, 0);
	tmp = pwd;
	pwd = ft_strjoin_line("OLDPWD=", pwd);
	ft_free(tmp);
	export_add(untils->env, pwd, untils);
	ft_free(pwd);
	return (0);
}

static void	cd_home(t_command *list, t_untils *untils)
{
	char	*line;
	char	*pwd;
	char	*tmp;

	line = NULL;
	if (cd_other(untils, list))
		return ;
	if (chdir(untils->home) == -1)
	{
		ft_free(untils->home);
		printf("cd: %s\n", strerror(errno));
		untils->status = 1;
		return ;
	}
	ft_free(untils->home);
	pwd = getcwd(line, 0);
	untils->home = pwd;
	pwd = ft_strjoin_line("PWD=", pwd);
	ft_free(untils->home);
	export_add(untils->env, pwd, untils);
	ft_free(pwd);
}

static void	f_cd_2(t_command *list, t_untils *untils)
{
	char	*pwd;
	char	*tmp;
	char	*line;

	pwd = getcwd(line, 0);
	tmp = pwd;
	pwd = ft_strjoin_line("PWD=", pwd);
	ft_free(tmp);
	export_add(untils->env, pwd, untils);
	ft_free(pwd);
}

int	f_cd(t_command *list, t_untils *untils)
{
	int		i;
	char	*line;
	char	*pwd;
	char	*tmp;

	if (!(list->next))
	{
		cd_home(list, untils);
		return (1);
	}
	line = NULL;
	pwd = getcwd(line, 0);
	tmp = pwd;
	pwd = ft_strjoin_line("OLDPWD=", pwd);
	ft_free(tmp);
	export_add(untils->env, pwd, untils);
	ft_free(pwd);
	list = list->next;
	if (chdir(list->command) == -1)
	{
		printf("cd: %s\n", strerror(errno));
		untils->status = 1;
	}
	f_cd_2(list, untils);
	return (i);
}
