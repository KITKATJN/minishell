#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
typedef struct			s_command
{
	char				*command; //название команды
	char				*argument; //аргументы команды
	char				*flag; //только для echo
	struct s_command	*next;
	struct s_command	*back;
}						t_command;

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
#endif
