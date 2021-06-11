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

static void	cd_home(t_command *list, t_untils *untils)
{
	char	*home;
	char	*line;
	int		i;
	char	*pwd;
	char	*tmp;

	line = NULL;
	home = find_home(untils);
	if (!home)
	{
		printf("cd : HOME not set\n");
		untils->status = 1;
		return ;
	}
	pwd = getcwd(line, 0);
	tmp = pwd;
	pwd = ft_strjoin_line("OLDPWD=", pwd);
	ft_free(tmp);
	export_add(untils->env, pwd, untils);
	ft_free(pwd);
	if (chdir(home) == -1)
	{
		ft_free(home);
		printf("cd: %s\n", strerror(errno));
		untils->status = 1;
		return ;
	}
	ft_free(home);
	pwd = getcwd(line, 0);
	home = pwd;
	pwd = ft_strjoin_line("PWD=", pwd);
	ft_free(home);
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
