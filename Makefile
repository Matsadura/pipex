CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = arr_func.c env_func.c errors.c execv_func.c fd_func.c pipex.c struct.c
NAME = pipex.a
LIBFT = libft/libft.a
OBJECT = $(SRC:.c=.o)

all: $(NAME) $(LIBFT)
	$(CC) $(CFLAGS) $(NAME) $(LIBFT)

$(LIBFT):
	make -C libft

$(NAME): $(OBJECT)
	ar rcs $(NAME) $(OBJECT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: clean fclean all re
.SECONDARY: $(OBJECT)
