#ifndef MINISHELL_H
#define MINISHELL_H

#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_history
{
	char *content;
	char *line;
	struct s_history *next;
	struct s_history *back;
}				t_history;

int			ft_strlen(char *str);
int			ft_putchar(int c);
char		*ft_strjoin(char *s1, char *s2);
t_history		*ft_lstnew(void *content);
void		ft_lstadd_back(t_history **lst, t_history *new);
char	*ft_strdup(const char *src);
char *backspace(char *str);
char		*ft_strjoin_line(char const *s1, char const *s2);
void clear_history(t_history **history);
int		ft_lstsize(t_history *lst);

#endif