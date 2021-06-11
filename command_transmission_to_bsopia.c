#include "minishell.h"

t_command	*command_transmission_to_bsopia(t_parser *list_of_command, t_untils *untils)
{
	t_cttb cttb;
	//t_command *cttb.commands;
	//t_parser *cttb.current;
	//int cttb.i;
	//int cttb.i_env;
	//int cttb.j_env;
	//char *cttb.env_tmp;
	//char *cttb.string_before_doolar;
	//char *cttb.command_tmp;
	//char *cttb.end_command;
	//char *cttb.str_from_my_env;
	//int cttb.i_for_str_before_dollar;
	//char *cttb.tmp;

	cttb.commands = 0;
	cttb.current = list_of_command;
	//printf_list(cttb.current);
	while (cttb.current)
	{
		cttb.i_env = 0;
		cttb.end_command = ft_calloc(1, 1);
		cttb.string_before_doolar = ft_calloc(ft_strlen(cttb.current->symbol) + 1, ft_strlen(cttb.current->symbol) + 1);
		cttb.i_for_str_before_dollar = 0;
		while (cttb.i_env < ft_strlen(cttb.current->symbol))
		{
			if (cttb.current->special_array[cttb.i_env] == 5 )//&& cttb.current->symbol[cttb.i_env + 1] != 0 && cttb.current->symbol[cttb.i_env + 1] != '?')
			{
				if (cttb.current->special_array[cttb.i_env + 1] != 0)
				{
				cttb.env_tmp = malloc(sizeof(char*) * (ft_strlen(cttb.current->symbol) - cttb.i_env) + 1);
				ft_bzero(cttb.env_tmp, ft_strlen(cttb.current->symbol) - cttb.i_env + 1);
				cttb.j_env = cttb.i_env + 1;
				cttb.i = 0;
				while (cttb.j_env < ft_strlen(cttb.current->symbol))
				{
					if (cttb.current->special_array[cttb.j_env] == 0 || cttb.current->special_array[cttb.j_env] == 5 || cttb.current->special_array[cttb.j_env] == 3 || (cttb.current->special_array[0] == 2 && cttb.current->special_array[cttb.j_env] == 2))
						break;
					if (cttb.current->symbol[cttb.j_env] == '?')
					{
						cttb.env_tmp[cttb.j_env - cttb.i_env - 1] = cttb.current->symbol[cttb.j_env];
						break ;
					}
					if (ft_isdigit (cttb.current->symbol[cttb.j_env]))
					{
						cttb.env_tmp[cttb.j_env - cttb.i_env - 1] = cttb.current->symbol[cttb.j_env];
						cttb.j_env++;
						break ;
					}
					cttb.env_tmp[cttb.j_env - cttb.i_env - 1] = cttb.current->symbol[cttb.j_env];
					cttb.j_env++;
				}
				//printf("-->%s\n", cttb.env_tmp);
				if (cttb.env_tmp[0] == '?')
					cttb.str_from_my_env = ft_strdup("$?+");
				else
					cttb.str_from_my_env = my_get_env(cttb.env_tmp, untils->env);
				if (cttb.str_from_my_env == 0)
					cttb.command_tmp = ft_calloc(1, 1);
				else
					cttb.command_tmp = cttb.str_from_my_env;// ft_strjoin(getenv(cttb.env_tmp), cttb.current->symbol + cttb.j_env);
				ft_free(cttb.env_tmp);
				cttb.end_command = ft_strjoin(cttb.end_command, cttb.string_before_doolar);
				cttb.end_command = ft_strjoin(cttb.end_command, cttb.command_tmp);
				ft_free(cttb.command_tmp);
				cttb.i_env = cttb.j_env;
				ft_bzero(cttb.string_before_doolar, ft_strlen(cttb.current->symbol) + 1);
				cttb.i_for_str_before_dollar = 0;
				continue ;
				}
			}
			if (cttb.i_env < ft_strlen(cttb.current->symbol))
				cttb.string_before_doolar[cttb.i_for_str_before_dollar] = cttb.current->symbol[cttb.i_env];
			cttb.i_for_str_before_dollar++;
			cttb.i_env++;
		}
		cttb.tmp = cttb.end_command;
		cttb.end_command = ft_strjoin(cttb.end_command, cttb.string_before_doolar);
		ft_free(cttb.tmp);
		ft_free(cttb.string_before_doolar);
		if (cttb.end_command[0] != '\0' || cttb.current->symbol[0] == '$')
		{
			ft_free(cttb.current->symbol);
			cttb.current->symbol = cttb.end_command;
		}
		if (cttb.current->special_array[0] == 9)
		{
			bsopia_func(cttb.commands, 2, untils);
			ft_lstclear_command(&cttb.commands);
			if (cttb.current->next == 0)
				break ;
			cttb.current = cttb.current->next;
		}
		ft_lstadd_back_parser(&cttb.commands, ft_lstnew_parser(ft_strdup(cttb.current->symbol), 0));
		cttb.current = cttb.current->next;
	}
	if (cttb.commands != 0)
	{
		bsopia_func(cttb.commands, 0, untils);
		ft_lstclear_command(&cttb.commands);
	}
	ft_lstclear_parser2(&list_of_command);
	return(cttb.commands);
}
