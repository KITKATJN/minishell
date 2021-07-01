#include "minishell.h"

int	check_quotes_start(char *str1)
{
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	while (i < ft_strlen(str1))
	{
		if (str1[i] != ' ' && str1[i] != '\'' && str1[i] != '\"')
			flag = 0;
		else if (str1[i] == ';')
			flag = 1;
		i++;
	}
	return (flag);
}

int	parser_into_list2_2(t_parser *current)
{
	if (current->next && (current->next->symbol[0] == '>'
			|| current->next->symbol[0] == '<'
			|| current->next->symbol[0] == ' '
			|| current->next->symbol[0] == ';'
			|| current->next->symbol[0] == '|'))
		return (1);
	return (0);
}

static void	assigning_symbols_to_command2(t_parser *start)
{
	t_parser	*temporary;
	t_parser	*current;

	current = start;
	while (current)
	{
		if (current->symbol[0] == '\0')
		{
			temporary = current;
			current = current->next;
			delete_current_parser2(temporary);
			continue ;
		}
		current = current->next;
	}
}

static void	assigning_symbols_to_command3(t_astc *astc)
{
	astc->str = ft_calloc(astc->i + 1, astc->i + 1);
	astc->special_array = ft_calloc(astc->i + 1, astc->i + 1);
	astc->i = 0;
	while (astc->new_start != astc->current)
	{
		if (astc->new_start->special != 1 && astc->new_start->special != 2)
		{
			astc->str[astc->i] = astc->new_start->symbol[0];
			astc->special_array[astc->i] = astc->new_start->special;
			astc->i++;
		}
		astc->new_start = astc->new_start->next;
	}
	if (astc->current->next == 0 && astc->current->special != -1)
	{
		if (astc->new_start->special != 1 && astc->new_start->special != 2)
		{
			astc->str[astc->i] = astc->new_start->symbol[0];
			astc->special_array[astc->i] = astc->new_start->special;
		}
	}
}

t_parser	*assigning_symbols_to_command(t_parser *start)
{
	t_astc	astc;

	astc.new_start = start;
	astc.i = 0;
	astc.j = 0;
	astc.list_of_command = 0;
	astc.current = start;
	while (astc.current)
	{
		if (astc.current->special != -1)
			astc.i++;
		if ((astc.current->special == -1 || astc.current->next == 0))
		{
			assigning_symbols_to_command3(&astc);
			ft_lstadd_back_parser2(&astc.list_of_command,
				ft_lstnew_parser2(astc.str, 0, astc.special_array));
			astc.i = 0;
			if (astc.new_start != 0)
				astc.new_start = astc.new_start->next;
		}
		astc.current = astc.current->next;
	}
	ft_lstclear_parser2(&start);
	assigning_symbols_to_command2(astc.list_of_command->next);
	return (astc.list_of_command);
}
