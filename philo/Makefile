FLAG = -Wall -Wextra -Werror -lpthread

NAME = philo

SRC = \
			main.c \
			utils.c \
			actions.c \
			init.c \
			threads.c

OBJS = $(SRC:.c=.o)

CC = cc

all: $(NAME)

$(NAME):	$(SRC)
	$(CC) $(FLAG) $(SRC) -o $(NAME)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
