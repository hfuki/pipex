NAME = pipex
SRCS = child.c path.c main.c pipex.c utils.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a


all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	make -C libft

clean :
	rm -f $(OBJS)
	make clean -C libft

fclean : clean
	rm -f $(NAME)
	make fclean -C libft

re : fclean all

.PHONY : all clean fclean re
