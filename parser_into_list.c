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
			//printf("element = %s\n", arr_of_command[i]);
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
	int				k;
	char			*str;

	// j = 0;
	// while (j < ft_strlen(argv))
	// {
	// 	printf("!+++!arr_of_command3[%d] = !%s!\n", j,arr_of_command[j]);
	// 	j++;
	// }
	i = 0;
	j = 0;
	while (i < ft_strlen(argv))
	{
		if (i == ft_strlen(argv) - 1)
			break ;
		//printf("++++++++++++++++++++++++++++++++++++++++++++%d %d\n", i, ft_strlen(argv));
		if (arr_of_command[i][0] != '\0' &&	arr_of_command[i][0] != '\'' && arr_of_command[i][0] != '\"')
		{
			//printf("1------------------------------------------\n");
			j = i;
			while (j < ft_strlen(argv))
			{
				//printf("************%d %d\n", j, ft_strlen(argv));
				if (arr_of_command[j][0] == '\0' || arr_of_command[j][0] == '\'' || arr_of_command[j][0] == '\"')
					break ;
				j++;
			}
			str = malloc(sizeof(char) * (j - i + 1));
			ft_bzero(str, (j - i + 1));
			k =	0;
			//printf("!!!i = %d j = %d  !%c! !%c!\n", i,j, arr_of_command[i][0], arr_of_command[j][0]);
			while (i + k < j)
			{
				str[k] = arr_of_command[i + k][0];
				arr_of_command[i + k][0] = '\0';
				k++;
			}
			free(arr_of_command[i]);
			arr_of_command[i] = str;
			str = 0;
			i += k - 1;
			//printf("i =%d\n",i);
			// while (++i < j)
			// 	arr_of_command[i][0] = '\0';
			//continue ;
		}
		i++;
	}

	// j = 0;
	// while (j < ft_strlen(argv))
	// {
	// 	printf("!!arr_of_command3[%d] = !%s!\n", j,arr_of_command[j]);
	// 	j++;
	// }
}

static	void		change_space_to_end_str(char **arr_of_command, char *argv, int flag)
{
	int				i;
	int j;

	i = 0;
	// j = 0;
	// while (j < ft_strlen(argv))
	// {
	// 	printf("1->arr_of_command3[%d] = !%c!\n", j,arr_of_command[j][0]);
	// 	j++;
	// }
	int t;
	while (i < ft_strlen(argv))
	{
		if (arr_of_command[i][0] == ' ' && i > flag)
			arr_of_command[i][0] = '\0';
		//printf("=---------------------------------------------------------------------------=\n");
		if (arr_of_command[i][0] == '\'')
		{
			t = i;
			i = delete_spaces(arr_of_command, argv, i, '\'');
			//printf("+++++arr = %s %d\n",arr_of_command[t], i);
			continue ;
		}
		if (arr_of_command[i][0] == '\"')
		{
			i = delete_spaces(arr_of_command, argv, i, '\"');
			continue ;
		}
		i++;
	}

	// j = 0;
	// while (j < ft_strlen(argv))
	// {
	// 	printf("->arr_of_command3[%d] = %c\n", j,arr_of_command[j][0]);
	// 	j++;
	// }
}

static	int		from_str_to_symb(char **arr_of_command, char *argv)
{
	int				i;
	int				flag;
	int				j;
	int				double_quotes;
	int				alone_quotes;
	int				check_quotes;

	flag = 1;
	i = 0;
	j = 0;
	while (j < ft_strlen(argv))
	{
		arr_of_command[j] = malloc(sizeof(char) * 2);
		ft_bzero(arr_of_command[j], 2);
		j++;
	}
	j = 0;
	while (i < ft_strlen(argv))
	{
		//arr_of_command[j] = malloc(sizeof(char) * 2);
		//ft_bzero(arr_of_command[j], 2);
		if (i >= ft_strlen(argv))
			break ;
		if (argv[i] == ';')
		{
			alone_quotes = 0;
			double_quotes = 0;
			check_quotes = i;
			while (check_quotes >= 0)
			{
				if (argv[check_quotes] == '\'')
					alone_quotes++;
				if (argv[check_quotes] == '\"')
					double_quotes++;
				check_quotes--;
			}
			//printf("---->>>%d alone = %d\n", double_quotes, alone_quotes);
			if (double_quotes % 2 == 0 && alone_quotes % 2 == 0)
				flag = 1;
		}
		//if (argv[i] == ' ')
		//	flag = 0;
		if (argv[i] == '\'' && flag)
		{
			if (i + 1 < ft_strlen(argv) && argv[i + 1] == '\'')
			{
				i += 2;
				continue ;
			}
		}
		if (argv[i] == '\"' && flag)
		{
			if (i + 1 < ft_strlen(argv) && argv[i + 1] == '\"')
			{
				i += 2;
				continue ;
			}
		}
		arr_of_command[j][0] = argv[i];
		//printf("arr_of_command[%d] = %c\n", j,arr_of_command[j][0]);
		arr_of_command[j][1] = '\0';
		if ((argv[i] == '\'' || argv[i] == '\"') && !flag)
			flag = 1;
		j++;
		i++;
	}
	while (j < ft_strlen(argv))
	{
		arr_of_command[j] = malloc(sizeof(char) * 1);
		arr_of_command[j][0] = '\0';
		j++;
	}

	// j = 0;
	// while (j < ft_strlen(argv))
	// {
	// 	printf("before !arr_of_command3[%d] = !%c!\n", j,arr_of_command[j][0]);
	// 	j++;
	// }

	flag = 0;
	i = 0;
	while (i < ft_strlen(argv))
	{
		if (arr_of_command[i][0] == ' ')
		{
			alone_quotes = 0;
			double_quotes = 0;
			check_quotes = i;
			while (check_quotes >= 0)
			{
				if (arr_of_command[check_quotes][0] == '\'')
					alone_quotes++;
				if (arr_of_command[check_quotes][0] == '\"')
					double_quotes++;
				check_quotes--;
			}
			//printf("---->>>%d alone = %d\n", double_quotes, alone_quotes);
			if (double_quotes % 2 == 0 && alone_quotes % 2 == 0)
			{
				flag = i;
				break ;
			}
		}
		i++;
	}
	//printf("flag = %d\n", flag);
	j = 0;
	int iterator;
	int number_of_quotes = 0;
	if (!flag)
		flag = ft_strlen(argv) - 1;
	//flag = 0;
	if (double_quotes > 0 || alone_quotes > 0)
	{
	while (j < flag)
	{
		if (arr_of_command[j][0] == '\'')
		{
			//printf("iterator = %d\n", j);
			iterator = j;
			while (iterator + 1 < ft_strlen(argv))
			{
				//printf("arrr1 = %s !%s!\n", arr_of_command[iterator], arr_of_command[iterator+1]);
				arr_of_command[iterator][0] = arr_of_command[iterator + 1][0];
				//printf("arrr2 = %s\n", arr_of_command[iterator]);
				iterator++;
			}
			arr_of_command[iterator][0] = '\0';//ft_strdup("");
			number_of_quotes++;
			j = 0;
		}
		else if (arr_of_command[j][0] == '\"')
		{
			//printf("iterator = %d\n", j);
			iterator = j;
			while (iterator + 1 < ft_strlen(argv))
			{
				//printf("arrr1 = %s !%s!\n", arr_of_command[iterator], arr_of_command[iterator+1]);
				arr_of_command[iterator][0] = arr_of_command[iterator + 1][0];
				//printf("arrr2 = %s\n", arr_of_command[iterator]);
				iterator++;
			}
			arr_of_command[iterator][0] = '\0';//ft_strdup("");
			number_of_quotes++;
			j = 0;
		}
		j++;
	}
	// j = 0;
	if (flag - number_of_quotes > -1 && number_of_quotes > 0)
	{
		//arr_of_command[flag - 1 - number_of_quotes][0] = ' ';
		//printf("************%d %d\n", flag, number_of_quotes);
		arr_of_command[flag - number_of_quotes][0] = '\0';
	}
	}



	j = 0;
	// while (j < ft_strlen(argv))
	// {
	// 	printf("!arr_of_command3[%d] = !%c!\n", j,arr_of_command[j][0]);
	// 	j++;
	// }
	return (flag - 3);
}

t_command			*parser_into_list(char *argv)
{
	int				i;
	int flag;
	char			**arr_of_command;

	i = 0;
	arr_of_command = malloc(sizeof(char*) * ft_strlen(argv));
	if (check_double_semicolon(argv) != 0)
		return (check_double_semicolon(argv));
	if (add_quotes(argv))
		argv = add_quotes(argv);
	flag = from_str_to_symb(arr_of_command, argv);
	change_space_to_end_str(arr_of_command, argv, flag);
	from_symb_to_command(arr_of_command, argv);
	return (make_list(arr_of_command, argv));
}
