#include "minishell.h"

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

	tmp = ft_lstnew(NULL);
	ft_lstadd_back(history, tmp);
	untils->flag_up_down = 0;
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
		// if (g_sig_f == 1)
		// {
		// 	// free(line);
		// 	// free(tmp->content);
		// 	// tmp->content = NULL;
		// 	// line = NULL;
		// 	while (tmp->back)
		// 		tmp = tmp->back;
		// 	if (tmp->content)
		// 		tmp->content = untils->first;
		// 	while (tmp->next)
		// 		tmp = tmp->next;
		// 	write(1, "\n", 1);
		// 	g_sig_f = 0;
		// 	return (tmp->content);
		// 	break ;
		// }

		ft_memset(buff, 0, 5);
		l = read (0, buff, 1);

		if (g_sig_f == 1)
		{
			ft_memset(buff, 0, 5);
			// buff[0] = '\n';
			write(1, "\n", 1);
			free(line);
			line = 0;
			g_sig_f = 0;
			return(0);
		}
		if (buff[0] == '\n')
		{
			write(1, "\n", 1);
			save = ft_strjoin_line(tmp->content, line);
			while (tmp->next)
				tmp = tmp->next;
			tmp->content = ft_strdup_b(save);
			ft_free(save);
			while (tmp->back)
			{
				if (tmp->line)
				{
					// printf("1--------------\n");
					// if (tmp->content != 0)
					// {
					// 	printf("hello %s\n", tmp->content); // здесь получаем ошибку связанную с двойным особождением памяти
					//ft_free(tmp->content);
					// }
					ft_free(tmp->content);
					tmp->content = ft_strdup_b(tmp->line);
				}
				tmp = tmp->back;
			}
			if (line && untils->flag == 1)
			{
				untils->first = ft_strdup_b(tmp->content);
				untils->flag = 0;
			}
			while (tmp->back)
				tmp = tmp->back;
			if (tmp->content)
			{
				//ft_free(tmp->content); // здесь мы получаем ошибку, что память была освобождена, когда пытаемся прочитать первый элемент истории несколько раз
				ft_free(tmp->content);
				tmp->content = ft_strdup_b(untils->first);
			}
			while (tmp->next)
				tmp = tmp->next;
			ft_free(line);
			return (ft_strdup_b(tmp->content));
		}
		else if (buff[0] == '\e')
		{
			read (0, b, 2);
			if (b[0] == '[' && b[1] == 'A')
			{
				if (tmp->back)
				{
					untils->flag_up_down = 1;
					tputs(tgetstr("rc", 0), 1, ft_putchar); //restore cursor
					tputs(tgetstr("ce", 0), 1, ft_putchar);
					if (line)
					{
						tmp->content = ft_strjoin_line(tmp->content, line);
						// ft_free(line);
					}
					tmp = tmp->back;
					write(1, tmp->content, ft_strlen_b(tmp->content));
				}
			}
			if (b[0] == '[' && b[1] == 'B')
			{
				if (tmp->next)
				{
					untils->flag_up_down = 1;
					tputs(tgetstr("rc", 0), 1, ft_putchar); //restore cursor
					tputs(tgetstr("ce", 0), 1, ft_putchar);
					if (line)
					{
						tmp->content = ft_strjoin_line(tmp->content, line);
						// ft_free(line);
					}
					tmp = tmp->next;
					write(1, tmp->content, ft_strlen_b(tmp->content));
				}
			}
		}
		else if (buff[0] == '\4' && !(ft_strlen(line)) && !(ft_strlen(tmp->content)))
		{
			printf("exit\n");
			// write(1, "exit\n", 5);
			// write(1, "\n", 1);
			ft_free(line);
			//фришить все что есть(структуры и так далее);
			exit(0);
		}
		if (!(strcmp(buff, "\177")))
		{
			if (untils->flag_up_down == 1)
			{
				tputs(tgetstr("rc", 0), 1, ft_putchar); //restore cursor  возмо
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
			if (ft_isprint(buff[0]))
				line = ft_strjoin_b(line, buff);
		}
	}
	ft_free(line);
	return (ft_strdup_b(tmp->content));
}

int main(int argc, char **argv, char **envp)
{
	// char *buff[2];
	struct termios term;
	struct termios term2;
	char *line;
	char *term_name;
	t_history *history;
	t_untils *untils;

	history = NULL;
	line = NULL;
	untils = init_untils(untils);
	term_name = "xterm-256color"; //костыль достать из envp, если нет то выходим из программы (везде где пользуемся переменными окружения проверяем есть ли она там)
	tcgetattr(0, &term);
	tcgetattr(0, &term2);
	//проверка на envp;
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 1;
	// signal(SIGINT, signal_c);
	// signal(SIGQUIT, SIG_IGN);
	tgetent(0, term_name);
	untils->env = copy_envp(envp, untils->env);
	while (1)
	{
		tcsetattr(0, TCSANOW, &term);
		signal(SIGINT, signal_c);
		signal(SIGQUIT, SIG_IGN);
		// g_sig_f = 0;
		tputs("$S> ", 1, ft_putchar);
		tputs(save_cursor, 1, ft_putchar);
		line = reading_str(term, &history, untils);
		// if (!line)
		// {
			clear_history(&history);
		// }
		untils->fd_in = 99;
		untils->fd_out = 99;
		tcsetattr(0, TCSANOW, &term2);
		if (line)
			main_parser(line, untils);
		ft_free(line);
	}
}
