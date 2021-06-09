#include "minishell.h"

static char *find_home(t_untils *untils)
{
	int i;
	char *home;

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

static void cd_home(t_command *list, t_untils *untils)
{
	char *home;
	char *line;
	int i;
	char *pwd;

	line  = NULL;
	home = find_home(untils);
	if (!home)
	{
		printf("cd : HOME not set\n");
		untils->status = 1;
		return ;
	}
	pwd = getcwd(line, 0);
	pwd = ft_strjoin_line("OLDPWD=", pwd);
	export_add(untils->env, pwd, untils);
	i = chdir(home);
	if (i == -1)
	{
		printf("! %s !\n", strerror(errno));
		untils->status = 1;
		return ;
	}
	pwd = getcwd(line, 0);
	pwd = ft_strjoin_line("PWD=", pwd);
	export_add(untils->env, pwd, untils);
}

int f_cd(t_command *list, t_untils *untils)
{
	int i;
	char *line;
	char *pwd;
	
	if (!(list->next))
	{
		cd_home(list,untils);
		return (1);
	}
	line = NULL;
	pwd = getcwd(line, 0);
	pwd = ft_strjoin_line("OLDPWD=", pwd);
	//возможно утечка line
	export_add(untils->env, pwd, untils);
	list = list->next;
	i = chdir(list->command);
	if (i == -1)
	{
		printf("! %s !\n", strerror(errno));
		untils->status = 1;
	}
	pwd = getcwd(line, 0);
	pwd = ft_strjoin_line("PWD=", pwd);
	export_add(untils->env, pwd, untils);
	//возможно утечка line
	return (i);
}
