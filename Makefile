CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRC = arr_func.c env_func.c errors.c execv_func.c fd_func.c pipex.c struct.c
NAME = pipex
LIBFT = libft/libft.a
OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJECT)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: clean fclean all re
