#include "minishell.h"

int flag_vniz_vverh;

static int count_word(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

void print_env(char **cp_env)
{
	int i;

	i = 0;
	while (cp_env[i] != NULL)
	{
		if (ft_strchr(cp_env[i], '='))
		{
			write(1, cp_env[i], ft_strlen_b(cp_env[i]));
			write(1, "\n", 1);
			i++;
		}
		else
			i++;
	}
}

char **sort_mass(char **str)
{
	int i;
	char *buf;
	int k;

	k = count_word(str);
	while (k - 1)
	{
		i = 0;
		while (str[i] != NULL)
		{
			if (str[i + 1] != NULL && (ft_strcmp(str[i],str[i + 1])) > 0)
			{
				buf = str[i];
				str[i] = str[i + 1];
				str[i + 1] = buf;
			}
			i++;
		}
		k--;
	}
	return (str);
}

void print_export(char **cp_env)
{
	int i;
	int k;
	int flag;

	i = 0;
	k = 0;
	cp_env = sort_mass(cp_env);
	while (cp_env[i] != NULL)
	{
		flag = 1;
		write(1, "declare -x ", 11);
		k = 0;
		while (cp_env[i][k] != '\0')
		{
			if (cp_env[i][k] != '\0')
				write(1, &cp_env[i][k], 1);
			if (cp_env[i][k] == '=')
			{
				write(1, "\"", 1);
				flag = 0;
			}
			k++;
		}
		if (flag == 0)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

char *reading_str(struct termios term, t_history **history, t_untils *untils)
{
	int l;
	char buff[5];
	char *line;
	char b[2];
	t_history *tmp;
	char *save;

	line = calloc(1, 1);
	tmp = ft_lstnew(NULL);
	ft_lstadd_back(history, tmp);
	flag_vniz_vverh = 0;
	line = NULL;
	while (tmp->back)
	{
		if (tmp->line == NULL)
			tmp->line = ft_strdup_b(tmp->content);
		tmp = tmp->back;
	}
	while (tmp->next)
		tmp = tmp->next;
	while (1)
	{
		l = read (0, buff, 1);
		if (buff[0] == '\n')
		{
			write(1, "\n", 1);
			// if (line2)
			// {
				save = ft_strjoin_line(tmp->content, line);
				while (tmp->next)
					tmp = tmp->next;
				tmp->content = ft_strdup_b(save);
				free(save);
				free(line);
				while (tmp->back)
				{
					if (tmp->line)
						tmp->content = ft_strdup_b(tmp->line);
					tmp = tmp->back;
				}
				// tmp->content = ft_strdup(tmp->line);
			// }
			// while (tmp->next)
			// 	tmp = tmp->next;
			// if (!strcmp(tmp->content, "pwd")) //отдельный файл будет где я буду смотреть команды и исполнять их || в strcmp не подавать NULL иначе сега, нужно написать свою функцию с защитой
			// 	get_pwd();
			// // if (!strncmp(tmp->content, "echo -n", 7)) //отдельный файл будет где я буду смотреть команды и исполнять их
			// // 	f_echo("hello", 0);
			// // else 									//отдельный файл будет где я буду смотреть команды и исполнять их
			// // 	f_echo("hello", 1);
			// if (!strcmp(tmp->content, "cd")) ////отдельный файл будет где я буду смотреть команды и исполнять их
			// 	f_cd("..");
			// if (!strcmp(tmp->content, "env"))
			// 	print_env(*cp_env);
			// if (!strcmp(tmp->content, "export"))
			// {
			// 	// *cp_env = export_add(*cp_env, "lol=1");
			// 	// *cp_env = export_add(*cp_env, "lol=2");
			// 	// *cp_env = export_add(*cp_env, "lol=3");
			// 	// *cp_env = export_add(*cp_env, "lol=4");
			// 	// *cp_env = export_add(*cp_env, "lol=5");
			// 	// *cp_env = export_add(*cp_env, "lol=6");
			// 	// *cp_env = export_add(*cp_env, "lol1=5");
			// 	*cp_env = export_add(*cp_env, "lol1=7");
			// 	*cp_env = export_add(*cp_env, "lol1=8");
			// 	*cp_env = export_add(*cp_env, "lol2= ");
			// }
			// if (!strcmp(tmp->content, "unset"))
			// {
			// 	*cp_env = f_unset_line(*cp_env, "lol");
			// 	*cp_env = f_unset_line(*cp_env, "lol1");
			// 	*cp_env = f_unset_line(*cp_env, "lol");
			// 	// int gg = 0;
			// 	// while(*cp_env[gg] != NULL)
			// 	// {
			// 	// 	printf("posle = | %s |", *cp_env[gg]);
			// 	// 	gg++;
			// 	// }
			// }
			if (untils->flag == 1)
			{
				untils->first = ft_strdup_b(tmp->content);
				untils->flag = 0;
			}
			while (tmp->back)
				tmp = tmp->back;
			tmp->content = untils->first;
			while (tmp->next)
				tmp = tmp->next;
			return (tmp->content);
		}
		else if (buff[0] == '\e')
		{
			read (0, b, 2);
			if (b[0] == '[' && b[1] == 'A')
			{
				if (tmp->back)
				{
					flag_vniz_vverh = 1;
					tputs(tgetstr("rc", 0), 1, ft_putchar); //restore cursor
					tputs(tgetstr("ce", 0), 1, ft_putchar);
					if (line)
					{
						tmp->content = ft_strjoin_line(tmp->content, line);
						line = 0;
					}
					tmp = tmp->back;
					write(1, tmp->content, ft_strlen_b(tmp->content));
				}
			}
			if (b[0] == '[' && b[1] == 'B')
			{
				if (tmp->next)
				{
					flag_vniz_vverh = 1;
					tputs(tgetstr("rc", 0), 1, ft_putchar); //restore cursor
					tputs(tgetstr("ce", 0), 1, ft_putchar);
					if (line)
					{
						tmp->content = ft_strjoin_line(tmp->content, line);
						line = 0;
					}
					tmp = tmp->next;
					write(1, tmp->content, ft_strlen_b(tmp->content));
				}
			}
		}
		if (!(strcmp(buff, "\177")))
		{
			if (flag_vniz_vverh == 1)
			{
				tputs(tgetstr("rc", 0), 1, ft_putchar); //restore cursor
				tputs(tgetstr("ce", 0), 1, ft_putchar); //чистит до конца строки
				if (ft_strlen_b(line) && line)
					line = backspace(line);
				else
					tmp->content = backspace(tmp->content);
				write(1, tmp->content, ft_strlen_b(tmp->content));
				write(1, line, ft_strlen_b(line));
			}
			else
			{
				tputs(tgetstr("rc", 0), 1, ft_putchar); //restore cursor
				tputs(tgetstr("ce", 0), 1, ft_putchar);
				line = backspace(line);
				write(1, line, ft_strlen_b(line));
			}
		}
		if ((strcmp(buff, "\177") && buff[0] != '\e'))
		{
			write (1, &buff[0], 1);
			line = ft_strjoin_b(line, buff);
		}
	}
	return (tmp->content);
}

int main(int argc, char **argv, char **envp)
{
	// char *buff[2];
	struct termios term;
	char *line;
	char *term_name;
	t_history *history;
	t_untils *untils;

	history = NULL;
	line = NULL;
	untils = malloc(sizeof(t_untils));
	untils->flag = 1;
	term_name = "xterm-256color";
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
	untils->env = copy_envp(envp, untils->env);
	while (1)
	{
		printf("Привет, САНЯ!\nесли ты это прочитал, то напиши мне\"я люблю мороженое без ванили\")))\nловлю сегу если ввести 'echo' без каких-либо параматеров \nесли ввести команду с пробелами перед ней, например : \"   env\" она выполнится, но в список команд не сохранится\n");
		tputs("$S> ", 1, ft_putchar);
		tputs(save_cursor, 1, ft_putchar);
		line = reading_str(term, &history, untils);
		//printf("line==!%s!\n", line);
		clear_history(&history);
		main_parser(line, untils);
	}
}
