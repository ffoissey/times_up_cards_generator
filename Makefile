CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = generator
LIB = libft/libft.a
SRC = generate.c

all: $(NAME)

$(NAME): $(LIB)
	$(CC) $(CFLAGS) $(SRC) -L./libft/ -lft -I./libft/includes -o $@

$(LIB): FORCE
	$(MAKE) -C ./libft/

FORCE:

clean:
	$(RM) ./cards.txt
	$(MAKE) clean -C ./libft/

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft/

re: fclean
	$(MAKE)

card:
	echo "Cards generate into cards.txt"
	./generator

.SILENT:
.PHONY: FORCE clean fclean re card
