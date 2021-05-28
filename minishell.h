#ifndef MINISHELL_H
#define MINISHELL_H

#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

typedef struct			s_untils
{
	char				**env;
	int					flag;
	char				*first;
	int					flag_up_down;

}						t_untils;

typedef struct			s_history
{
	char				*content;
	char				*line;
	struct s_history	*next;
	struct s_history	*back;
}						t_history;

typedef struct			s_parser
{
	char				*symbol;
	int					special;//1-' 2-" 3-\ 4-? 5-$ (-1)-незначащий пробел 0-экранированный символ 7-обычный символ
	struct s_parser		*next;
	struct s_parser		*back;
	int					*special_array;
}						t_parser;

typedef struct			s_command
{
	char				*command; //название команды
	char				*argument; //аргументы команды
	char				*flag; //только для echo
	struct s_command	*next;
	struct s_command	*back;
	int					error;
	char				*redir_right;
	char				*redir_double_right;
	char				*redir_left;
}						t_command;

int						ft_strlen_b(char *str);
int						ft_putchar(int c);
char					*ft_strjoin_b(char *s1, char *s2);
t_history				*ft_lstnew(void *content);
void					ft_lstadd_back(t_history **lst, t_history *new);
char					*ft_strdup_b(const char *src);
char					*backspace(char *str);
char					*ft_strjoin_line(char const *s1, char const *s2);
void					clear_history(t_history **history);
int						ft_lstsize(t_history *lst);
void					get_pwd();
int						f_echo(char *str, int i);
int						f_cd(t_command *list, t_untils *untils);
char					**copy_envp(char **envp, char **cp_env);
char					**export_add(char **cp_env, char *str, t_untils *untils);
char					**f_unset_line(char **env, char *str);
t_command				*check_double_semicolon(char *argv);
t_command				*ft_lstnew_parser(void *command, void *flag);
t_command				*parser_into_list(char *argv);
void					ft_lstadd_back_parser(t_command **lst, t_command *new);
char					*add_quotes(char *str);
void					delete_tcommand(t_command *command);
void					ft_perror(char *error);
void					parse_add_semicolon_to_end(t_command *start);
void					pars_to_command(t_command *start);
int						delete_spaces(char **arr_of_command, char *argv, int i, char delimiter);
char					*ft_check_command(char *command);
void					main_parser(char *str, t_untils *untils);
void					bsophia_function(t_command *list, t_untils *untils);
int						ft_lstsize_2(t_command *lst);
void					print_env(char **cp_env);
void					print_export(char **cp_env);
int						check_name(char *str);
int						ft_strcmp(char *str, char *str1);

t_command				*parser_into_list_2(char *str, t_untils *untils);
void					delete_current_parser(t_command *current);
void					ft_lstadd_back_parser2(t_parser **lst, t_parser *new);
t_parser				*ft_lstnew_parser2(char	*symbol, int special, int *special_array);
void					bsopia_func(t_command *com, int i, t_untils *untils);

#endif
