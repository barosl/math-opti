.PHONY: c clean

NAME = math-opti
OBJS = main.o

CFLAGS = -Wall -Werror -Wc++-compat

$(NAME): $(OBJS)
	$(CC) -o $@ $+

c: clean
clean:
	rm -f $(NAME) $(OBJS)
