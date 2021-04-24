#include "minishell.h"

int flag_vniz_vverh;

void print_list(t_history *his)
{
	t_history *temp;

	temp = his;
	while(temp)
	{
		printf("%s\n", temp->content);
		temp = temp->back;
	}
}

char *reading_str(struct termios term, t_history **history)
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
			// printf("!!!%s\n", line);
			if (line)
			{
				tmp->content = ft_strjoin_line(tmp->content, line);
			}
			free(line);
			// printf("%s\n", tmp->content);
			// if (tmp->content == NULL)
			// 	tmp->back->next = NULL;
			// printf("%s\n", tmp->content);
			break ;
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
					write(1, "$> ", 3);
					tputs(restore_cursor, 1, ft_putchar);
					if (line)
					{
						tmp->content =ft_strjoin_line(tmp->content, line);
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
					write(1, "$> ", 3);
					tputs(restore_cursor, 1, ft_putchar);
					if (line)
					{
						tmp->content =ft_strjoin_line(tmp->content, line);
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
				write(1, "$> ", 3);
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
				tputs(restore_cursor, 1, ft_putchar);
				tputs(delete_line, 1, ft_putchar);
				write(1, "$> ", 3);
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
	int l;
	char *line;
	char *term_name;
	t_history *history;
	t_history *tmp;

	
	history = NULL;
	term_name = "xterm-256color";
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
	
	while (1)
	{
		write(1, "$> ", 3);
		tputs(save_cursor, 1, ft_putchar);
		line = reading_str(term, &history);
		clear_history(&history);
		//parser(tmp->content)
	}
}
