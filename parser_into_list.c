#include "minishell.h"

static	t_command	*make_list(char **arr_of_command, char *argv)
{
	t_command		*start;
	t_command		*new_element;
	int				i;

	start = 0;
	new_element = 0;
	i = 0;
	while (i < ft_strlen(argv))
	{
		if (arr_of_command[i][0] != '\0')
		{
			new_element = ft_lstnew_parser(ft_strdup(arr_of_command[i]), 0);
			ft_lstadd_back_parser(&start, new_element);
		}
		i++;
	}
	i = 0;
	while (i < ft_strlen(argv))
	{
		free(arr_of_command[i]);
		i++;
	}
	free(arr_of_command);
	return (start);
}

static	void		from_symb_to_command(char **arr_of_command, char *argv)
{
	int				i;
	int				j;

	i = 0;
	while (i < ft_strlen(argv))
	{
		if (arr_of_command[i][0] != '\0' &&
			arr_of_command[i][0] != '\'' && arr_of_command[i][0] != '\"')
		{
			j = i;
			while (j < ft_strlen(argv))
			{
				if (arr_of_command[j][0] == '\0')
					break ;
				j++;
			}
			free(arr_of_command[i]);
			arr_of_command[i] = ft_substr(argv, i, j - i);
			while (++i < j)
				arr_of_command[i][0] = '\0';
			continue ;
		}
		i++;
	}
}

static	void		change_space_to_end_str(char **arr_of_command, char *argv)
{
	int				i;

	i = 0;
	while (i < ft_strlen(argv))
	{
		if (arr_of_command[i][0] == ' ')
			arr_of_command[i][0] = '\0';
		if (arr_of_command[i][0] == '\'')
		{
			i = delete_spaces(arr_of_command, argv, i, '\'');
			continue ;
		}
		if (arr_of_command[i][0] == '\"')
		{
			i = delete_spaces(arr_of_command, argv, i, '\"');
			continue ;
		}
		i++;
	}
}

static	char		**from_str_to_symb(char **arr_of_command, char *argv)
{
	int				i;

	i = 0;
	arr_of_command = malloc(sizeof(char*) * ft_strlen(argv));
	while (i < ft_strlen(argv))
	{
		arr_of_command[i] = malloc(sizeof(char) * 2);
		arr_of_command[i][0] = argv[i];
		arr_of_command[i][1] = '\0';
		i++;
	}
	return (arr_of_command);
}

t_command			*parser_into_list(char *argv)
{
	int				i;
	char			**arr_of_command;

	i = 0;
	if (check_double_semicolon(argv) != 0)
		return (check_double_semicolon(argv));
	if (add_quotes(argv))
		argv = add_quotes(argv);
	arr_of_command = from_str_to_symb(arr_of_command, argv);
	change_space_to_end_str(arr_of_command, argv);
	from_symb_to_command(arr_of_command, argv);
	return (make_list(arr_of_command, argv));
}
