CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = arr_func.c env_func.c errors.c execv_func.c fd_func.c pipex.c struct.c
SRC_BONUS = arr_func_bonus.c env_func_bonus.c errors_bonus.c execv_func_bonus.c fd_func_bonus.c pipex_bonus.c struct_bonus.c heredoc_func_bonus.c errors2_bonus.c
NAME = pipex
LIBFT = libft/libft.a
OBJECT = $(SRC:.c=.o)
OBJECT_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJECT)
	rm -f $(OBJECT_BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

bonus: $(SRC_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_BONUS) $(LIBFT) -o $(NAME)

re: fclean all

.PHONY: clean fclean all re
