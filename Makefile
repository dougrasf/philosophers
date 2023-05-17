FLAG = -Wall -Wextra -Werror -lpthread

NAME = philo

INC = -I ./include

SRC = \
			./src/main.c \
			./src/utils.c \
			./src/actions.c

OBJS = $(SRC:.c=.o)

CC = cc

all: $(NAME)

$(NAME):	$(SRC)
	$(CC) $(FLAG) $(SRC) $(INC) -o $(NAME)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re