#include "minishell.h"

static void echo_2(t_command *list)
{
	int i;
	char *line;

	i = 1;
	line = NULL;
	if (!list->next)
	{
		write(1, "\n", 1);
		return ;
	}
	list = list->next;
	if ((!(ft_strcmp(list->command, "-n"))))
	{
			i = 0;
			list = list->next;
	}
	while (list && ft_strcmp(list->command, "|") && ft_strcmp(list->command, ";"))
	{
		line = ft_strjoin_line(line, list->command);
		if (ft_lstsize_2(list) != 1)
			line = ft_strjoin_line(line, " ");
		list = list->next;
	}
	f_echo(line, i);
}

void bsophia_function(t_command *list, t_untils *untils)
{
	printf("bsophia first command =====> %s\n", list->command);
	if (!(ft_strcmp(list->command, "echo")))
		echo_2(list);
	if (!(ft_strcmp(list->command, "pwd")))
		get_pwd(); //сместить указатель и установить после пайпа или редиректа(до следующей исполняющей команды)
	if (!(ft_strcmp(list->command, "cd")))
	{
		printf(" cd = %d\n", f_cd(list, untils));//при ошибках возвращает -1 и ставит errno в должное значение/ сделать менеджмент ошибок
	}
	if (!(ft_strcmp(list->command, "env")))
		print_env(untils->env);
	if (!(ft_strcmp(list->command, "export")))
	{
		if (!(list->next))
		{
			print_export(untils->env);
			return ;
		}
		list = list->next;
		while (list->next)
		{
			if (check_name(list->command))
			{
				printf("export error\n");
				return ;
			}
			list = list->next;
		}
		if (check_name(list->command))
		{
			printf("export error\n");
			return ;
		}
		while (list->back)
		{
			if (!(ft_strcmp(list->command, "export")))
				break ;
			list = list->back;
		}
		while (list->next)
		{
			if (list->next)
			{
				list = list->next;
				export_add(untils->env, list->command, untils);
			}
		}
	}
	if (!(ft_strcmp(list->command, "unset")))
	{
		if (list->next)
		{
			list = list->next;
			untils->env = f_unset_line(untils->env, list->command);
		}
	}
}
