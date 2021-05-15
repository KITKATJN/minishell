#include "minishell.h"

int f_cd(t_command *list, t_untils *untils)
{
	int i;
	char *line;
	char *pwd;
	
	if (!(list->next))
		return (0);
	line = NULL;
	pwd = getcwd(line, 0);
	pwd = ft_strjoin_line("OLDPWD=", pwd);
	//возможно утечка line
	export_add(untils->env, pwd, untils);
	list = list->next;
	i = chdir(list->command);
	pwd = getcwd(line, 0);
	pwd = ft_strjoin_line("PWD=", pwd);
	export_add(untils->env, pwd, untils);
	//возможно утечка line
	return (i);
}
