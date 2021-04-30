NAME 	= minishell

DIR 	= .

LIST 	=	backspace.c \
			cd.c \
			clear_history.c copy_envp.c echo.c \
			export.c ft_lstadd_back.c ft_lstnew.c \
			ft_lstsize.c ft_strdup.c ft_strjoin_line.c \
			main.c pwd.c unset.c untils_func.c	
OBJDIR	=	objs/

OBJ 	=	$(LIST:.c=.o)
OBJS	= 	$(addprefix $(OBJDIR), $(OBJ))

FLAGS 	= -Wall -Wextra -Werror -I$(DIR)

CC		= gcc



.c.o:
	$(CC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) -ltermcap -O3 $(OBJS) -o $(NAME)

$(OBJDIR)%.o: %.c Makefile
	mkdir -p $(OBJDIR)
	gcc -c $< -o $@
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re bonus
