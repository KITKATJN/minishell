#ifndef HEAD_H
#define HEAD_H

typedef struct			s_command
{
	char				*command;
	char				*flag;
	struct s_command	*next;
	struct s_command	*back;
}						t_command;

#endif
