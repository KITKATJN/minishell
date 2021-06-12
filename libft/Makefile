NAME = libft.a

SRCS = ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strnstr.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_split.c \

SRCSB = ft_lstnew.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstiter.c \
	ft_lstmap.c \

CFLAGS = -Wall -Werror -Wextra

HEAD = libft.h

OBJ	= $(SRCS:.c=.o)
OBJ_B	= $(SRCSB:.c=.o)

#HFLAGS = -I $(HEAD)
HFLAGS	= -I ./re
OBJRID	= objs/

OBJS	= $(addprefix $(OBJ_DIR), $(OBJ))
OBJS_B	= $(addprefix $(OBJ_DIR), $(OBJ_B))

OBJ_DIR	= objs/

RM	= rm -f

CC = gcc

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	gcc ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

bonus: $(OBJS_B) $(OBJS)
	ar rc $(NAME) $(OBJS_B) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

so:
	$(CC) -c -fPIC $(CFLAGS) $(SRCS)
	gcc  -shared -o libft.so $(OBJS)

clean:
	@rm -rf $(OBJ_DIR)
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

.SILENT: fclean clean all re $(NAME) $(OBJS) $(OBJS_B) $(OBJRID) bonus
