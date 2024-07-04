 CC = cc  -g3 -pthread #-Wall -Wextra -Werror

NAME = philo

SRC = \
utils.c\
main.c\
eat.c\

all: $(NAME)

OBJS = $(SRC:.c=.o)

$(NAME) : $(LIBFT) $(OBJS) 
	ar -rcs $(NAME) $(OBJS)
	$(CC) $(NAME) -o philosopher

clean: 
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f philosopher
	rm -f a.out

re: fclean all

.PHONY: all clean fclean re