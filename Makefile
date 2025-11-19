NAME    = pipex

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude

SRC_DIR = src

SRC     = $(SRC_DIR)/pipex.c \
          $(SRC_DIR)/utils.c

OBJ     = $(SRC:.c=.o)

RM      = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

