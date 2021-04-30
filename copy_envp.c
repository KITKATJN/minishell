#include "minishell.h"

char **copy_envp(char **envp, char **cp_env)
{
	int i;

	i = 0;
	while(envp[i] != NULL)
		i++;
	i++;
	cp_env = (char**)malloc(i * sizeof(char*));
	i = 0;
	while(envp[i] != NULL)
	{
		cp_env[i] = ft_strdup(envp[i]);
		i++;
	}
	cp_env[i] = NULL;
	return(cp_env);
}
