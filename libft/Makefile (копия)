NAME 	= libft.a

DIR 	= .

LIST 	=	ft_atoi.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memset.c \
			ft_strdup.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strlcat.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlcpy.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_isascii.c \
			ft_calloc.c \
			ft_memmove.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_strtrim.c \
			ft_split.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c 


OBJ 	=	$(LIST:.c=.o)

BONUS_L =	ft_lstsize.c \
			ft_lstnew.c \
			ft_lstlast.c \
			ft_lstadd_front.c \
			ft_lstadd_back.c \
			ft_lstiter.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstmap.c 

BONUS_O =	$(BONUS_L:.c=.o)

FLAGS 	= -Wall -Wextra -Werror -I$(DIR)
CC		= gcc

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

bonus: $(BONUS_O) $(OBJ)
	ar rc $(NAME) $(BONUS_O) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ) $(BONUS_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
