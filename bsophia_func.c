#include "minishell.h"

static void echo_2(t_command *list)
{
	int i;
	char *line;

	i = 1;
	line = NULL;
	list = list->next;
	if ((!(strcmp(list->command, "-n"))))
	{
			i = 0;
			list = list->next;
	}
	while (list && strcmp(list->command, "|") && strcmp(list->command, ";"))
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
	if (!(strcmp(list->command, "echo")))
		echo_2(list);
	if (!(strcmp(list->command, "pwd")))
		get_pwd(); //сместить указатель и установить после пайпа или редиректа(до следующей исполняющей команды)
	if (!(strcmp(list->command, "cd")))
		printf(" cd = %d\n", f_cd(list));//при ошибках возвращает -1 и ставит errno в должное значение/ сделать менеджмент ошибок
	if (!(strcmp(list->command, "env")))
		print_env(untils->env);
	if (!(strcmp(list->command, "export")))
	{
		list = list->next;
		export_add(untils->env, list->command, untils);
	}
}
