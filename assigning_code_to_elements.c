#include "minishell.h"

static t_parser	*helper_function2(t_parser *start, int *count_1, int *i, char *str)
{
	char *c;

	c = malloc(sizeof(char) * 2);
	ft_bzero(c, 2);
	c[0] = str[*i];
	if (str[*i] == '|' && *count_1 % 2 == 0)
		{
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(c), 20, 0));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
		}
		else if (str[*i] == '>' && *count_1 % 2 == 0)
		{
			if (*i + 1 < ft_strlen(str) && str[*i + 1] == '>')
			{
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 29, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 29, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
				*i += 1;
			}
			else
			{
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 19, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
			}
		}
		else if (str[*i] == '<' && *count_1 % 2 == 0)
		{
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 18, 0));
				ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
		}
		else
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 7, 0));
		//printf("2-------->%s\n", start->symbol);
		return (start);
}

static t_parser	*helper_function1(t_parser *start, int *count_1,int *i, char *str)
{
	char *c;

	c = malloc(sizeof(char) * 2);
	ft_bzero(c, 2);
	c[0] = str[*i];
		if (str[*i] == '\\')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 3, 0));
		else if (str[*i] == '\"')
		{
			*count_1 += 1;
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 2, 0));
		}
		else if (str[*i] == '\'')
		{
			*count_1 += 1;
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 1, 0));
		}
		else if (str[*i] == '?')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 4, 0));
		else if (str[*i] == '$')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 5, 0));
		else if (str[*i] == ' ')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, -1, 0));
		else if (str[*i] == ';' && *count_1 % 2 == 0)
		{
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(c, 9, 0));
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(ft_strdup(" "), -1, 0));
		}
		else
		{
			start = helper_function2(start, count_1, i, str);
			free(c);
		}
	//printf("start = %s\n", start->symbol);
	return (start);
}


t_parser	*assigning_code_to_elements(char *str)
{
	t_parser	*start;
	int			*i;
	int			*count_1;
	char		*c;
	int			flag_delete_probel;

	i = malloc(sizeof(int));
	count_1 = malloc(sizeof(int));
	*i = 0;
	*count_1 = 0;
	start = 0;
	flag_delete_probel = 0;
	while (*i < ft_strlen(str))
	{
		if (str[*i] == ' ' && !flag_delete_probel)
		{
			*i += 1;
			continue ;
		}
		//printf("-------->%d\n", *i);
		start = helper_function1(start, count_1, i, str);
		flag_delete_probel = 1;
		//printf("1-------->%s\n", start->symbol);
		*i += 1;
		//printf("2-------->%d\n", *i);
		//free(c);
	}
	free(str);
	//printf("-->%p\n", start);
	return (start);
}
