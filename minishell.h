#ifndef MINISHELL_H
#define MINISHELL_H

#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct			s_history
{
	char				*content;
	char				*line;
	struct s_history	*next;
	struct s_history	*back;
}						t_history;

typedef struct			s_command
{
	char				*command; //название команды
	char				*argument; //аргументы команды
	char				*flag; //только для echo
	struct s_command	*next;
	struct s_command	*back;
}						t_command;

int						ft_strlen(char *str);
int						ft_putchar(int c);
char					*ft_strjoin(char *s1, char *s2);
t_history				*ft_lstnew(void *content);
void					ft_lstadd_back(t_history **lst, t_history *new);
char					*ft_strdup(const char *src);
char					*backspace(char *str);
char					*ft_strjoin_line(char const *s1, char const *s2);
void					clear_history(t_history **history);
int						ft_lstsize(t_history *lst);
void					get_pwd();
int						f_echo(char *str, int i);
int						f_cd(char *str);
char					**copy_envp(char **envp, char **cp_env);
char					**export_add(char **cp_env, char *str);
char					**f_unset_line(char **env, char *str);

#endif