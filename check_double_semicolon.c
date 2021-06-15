#include "minishell.h"

static	void	check_double_semicolon4(char *argv, t_cse *cse)
{
	cse->i++;
	while (argv[cse->i] == ' ')
		cse->i++;
}

static	void	check_double_semicolon3(char *argv, t_cse *cse)
{
	cse->i++;
	while (argv[cse->i] != '\"')
		cse->i++;
	cse->i++;
}

static	void	check_double_semicolon2(char *argv, t_cse *cse)
{
	cse->i++;
	while (argv[cse->i] != '\'' && cse->i < ft_strlen(argv) - 1)
		cse->i++;
	cse->i++;
}

t_command	*check_double_semicolon(char *argv)
{
	t_cse	cse;

	if (!argv)
		return (0);
	cse.i = -1;
	while (++cse.i < ft_strlen(argv) - 1)
	{
		if (argv[cse.i] == '\'')
		{
			check_double_semicolon2(argv, &cse);
			continue ;
		}
		if (argv[cse.i] == '\"')
		{
			check_double_semicolon3(argv, &cse);
			continue ;
		}
		if (argv[cse.i] == ';' && cse.i < ft_strlen(argv) - 1)
		{
			check_double_semicolon4(argv, &cse);
			if (argv[cse.i] == ';')
				return (ft_lstnew_parser("error with double semcicolon", "error"));
			continue ;
		}
	}
	return (0);
}
