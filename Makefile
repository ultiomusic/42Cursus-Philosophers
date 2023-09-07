NAME = philo

INC 	= includes/philo.h

SRC		=	src/philo.c\
			src/init.c\
			src/utils.c\
			src/setter_getter.c\
			src/setter_getter2.c\
			src/start_process.c\
			src/end_process.c\
			src/actions.c\

CC 		= gcc

FLAGS	= -Wall -Wextra -Werror -pthread

OBJS 	= $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME) $(OBJS) $(INC)

%.o: %.c $(INC)
		$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
