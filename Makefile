CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = generator
LIB = libft/libft.a
SRC = sources/generate.c

all: $(NAME)

$(NAME): $(LIB)
	$(CC) $(CFLAGS) $(SRC) -L./libft/ -lft -I./libft/includes -o $@

$(LIB): FORCE
	$(MAKE) -C ./libft/

FORCE:

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) ./cards.txt
	$(MAKE) fclean -C ./libft/

re: fclean
	$(MAKE)

card:
	echo "Cards generate into cards.txt"
	./generator

.SILENT:
.PHONY: FORCE clean fclean re card
