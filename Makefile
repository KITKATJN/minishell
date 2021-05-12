NAME 	= minishell

DIR 	= .

LIST 	=	backspace.c \
			cd.c \
			clear_history.c copy_envp.c echo.c \
			export.c ft_lstadd_back.c ft_lstnew.c \
			ft_lstsize.c ft_strdup.c ft_strjoin_line.c \
			main.c pwd.c unset.c untils_func.c \
			add_quotes.c command_list.c check_double_semicolon.c \
			delete_spaces.c delete_tcommand.c ft_check_command.c \
			ft_perror.c main_parser.c pars_to_command.c \
			parse_add_semicolon_to_end.c parser_into_list.c

OBJDIR	=	objs/

OBJ 	=	$(LIST:.c=.o)
OBJS	= 	$(addprefix $(OBJDIR), $(OBJ))

FLAGS 	= -Wall -Wextra -Werror -I$(DIR)

CC		= gcc



.c.o:
	$(CC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) -ltermcap -O3 $(OBJS) libft.a -o $(NAME) #-fsanitize=address

$(OBJDIR)%.o: %.c Makefile
	mkdir -p $(OBJDIR)
	gcc -c $< -o $@
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re bonus
