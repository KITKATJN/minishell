#include "minishell.h"

t_command *check_double_semicolon(char *argv)
{
	int i = 0;
	while (i < ft_strlen(argv) - 1)
	{
		if (argv[i] == '\'')
		{
			i++;
			while(argv[i] != '\'')
				i++;
			i++;
			continue ;
		}
		if (argv[i] == '\"')
		{
			//printf("i!!!**%d\n", i);
			i++;
			while(argv[i] != '\"')
			{
				//printf("argvi = %c\n", argv[i]);
				i++;
			}
			i++;
			//printf("i!!!%d\n", i);
			continue ;
		}
		if (argv[i] == ';' && i < ft_strlen(argv) - 1)
		{
			//printf("1argv = %c i = %d\n", argv[i], i);
			i++;
			while (argv[i] == ' ')
				i++;
			//printf("2argv = %c i = %d\n", argv[i], i);
			if (argv[i] == ';')
				return (ft_lstnew_parser("error with double semicolon", "error"));
			continue ;
		}
		i++;
	}
	return (0);
}
