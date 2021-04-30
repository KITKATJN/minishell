#include "minishell.h"

int flag_vniz_vverh;

void print_env(char **cp_env)
{
	int i;

	i = 0;
	while (cp_env[i] != NULL)
	{
		write(1, cp_env[i], ft_strlen(cp_env[i]));
		write(1, "\n", 1);
		i++;
	}
}

char *reading_str(struct termios term, t_history **history, char ***cp_env)
{
	int l;
	char buff[5];
	char *line;
	char b[2];
	t_history *tmp;

	line = calloc(1, 1);
	tmp = ft_lstnew(NULL);
	ft_lstadd_back(history, tmp);
	flag_vniz_vverh = 0;
	line = NULL;
	while (1)
	{
		l = read (0, buff, 1);
		if (buff[0] == '\n')
		{
			write(1, "\n", 1);
			if (line)
				tmp->content = ft_strjoin_line(tmp->content, line);
			free(line);
			if (!strcmp(tmp->content, "pwd")) //отдельный файл будет где я буду смотреть команды и исполнять их || в strcmp не подавать NULL иначе сега, нужно написать свою функцию с защитой
				get_pwd();
			if (!strncmp(tmp->content, "echo -n", 7)) //отдельный файл будет где я буду смотреть команды и исполнять их
				f_echo("hello", 0);
			else 									//отдельный файл будет где я буду смотреть команды и исполнять их
				f_echo("hello", 1);
			if (!strcmp(tmp->content, "cd")) ////отдельный файл будет где я буду смотреть команды и исполнять их
				f_cd("..");
			if (!strcmp(tmp->content, "env"))
				print_env(*cp_env);
			if (!strcmp(tmp->content, "export"))
			{
				// *cp_env = export_add(*cp_env, "lol=1");
				// *cp_env = export_add(*cp_env, "lol=2");
				// *cp_env = export_add(*cp_env, "lol=3");
				// *cp_env = export_add(*cp_env, "lol=4");
				// *cp_env = export_add(*cp_env, "lol=5");
				// *cp_env = export_add(*cp_env, "lol=6");
				// *cp_env = export_add(*cp_env, "lol1=5");
				*cp_env = export_add(*cp_env, "lol1=7");
				*cp_env = export_add(*cp_env, "lol1=8");
				*cp_env = export_add(*cp_env, "lol2= ");
			}
			if (!strcmp(tmp->content, "unset"))
			{
				*cp_env = f_unset_line(*cp_env, "lol");
				*cp_env = f_unset_line(*cp_env, "lol1");
				*cp_env = f_unset_line(*cp_env, "lol");
				// int gg = 0;
				// while(*cp_env[gg] != NULL)
				// {
				// 	printf("posle = | %s |", *cp_env[gg]);
				// 	gg++;
				// }
			}
			return (tmp->content);
			// break ;
		}
		else if (buff[0] == '\e')
		{
			read (0, b, 2);
			if (b[0] == '[' && b[1] == 'A')
			{
				if (tmp->back)
				{
					flag_vniz_vverh = 1;
					tputs(delete_line, 1, ft_putchar);
					// write(1, "$> ", 3);
					tputs("$S> ", 1, ft_putchar);
					tputs(restore_cursor, 1, ft_putchar); 
					if (line)
					{
						tmp->content = ft_strjoin_line(tmp->content, line);
						line = 0;
					}
					tmp = tmp->back;
					write(1, tmp->content, ft_strlen(tmp->content));
				}
			}
			if (b[0] == '[' && b[1] == 'B')
			{
				if (tmp->next)
				{
					flag_vniz_vverh = 1;
					tputs(delete_line, 1, ft_putchar);
					// write(1, "$> ", 3);
					tputs("$S> ", 1, ft_putchar);
					tputs(restore_cursor, 1, ft_putchar);
					if (line)
					{
						tmp->content = ft_strjoin_line(tmp->content, line);
						line = 0;	
					}
					tmp = tmp->next;
					write(1, tmp->content, ft_strlen(tmp->content));
				}
			}
		}
		if (!(strcmp(buff, "\177")))
		{
			if (flag_vniz_vverh == 1)
			{
				tputs(delete_line, 1, ft_putchar);
				tputs("$S> ", 1, ft_putchar);
				tputs(restore_cursor, 1, ft_putchar);
				if (ft_strlen(line) && line)
				{
					line = backspace(line);
				}
				else
					tmp->content = backspace(tmp->content);
				write(1, tmp->content, ft_strlen(tmp->content));
				write(1, line, ft_strlen(line));
			}
			else
			{
				tputs(delete_line, 1, ft_putchar);
				// write(1, "$> ", 3);
				tputs("$S> ", 1, ft_putchar);
				tputs(restore_cursor, 1, ft_putchar);
				line = backspace(line);
				write(1, line, ft_strlen(line));
			}
		}
		if ((strcmp(buff, "\177") && buff[0] != '\e'))
		{
			write (1, &buff[0], 1);
			line = ft_strjoin(line, buff);
		}
	}
	return (tmp->content);
}

int main(int argc, char **argv, char **envp)
{
	char *buff[2];
	struct termios term;
	char *line;
	char *term_name;
	t_history *history;
	char **cp_env;

	
	history = NULL;
	line = NULL;
	term_name = "xterm-256color";
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
	cp_env = copy_envp(envp, cp_env);
	
	while (1)
	{
		// write(1, "$> ", 3);
		tputs("$S> ", 1, ft_putchar);
		tputs(save_cursor, 1, ft_putchar);
		line = reading_str(term, &history, &cp_env);
		clear_history(&history);
		//parser(line); //вызов парсера
	}
}
