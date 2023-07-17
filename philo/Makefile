NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread
DEBUG = -g -fsanitize=address
THREAD_DEBUG = -g -fsanitize=thread

LIB = philo.h

SRC =	philo.c\
		utils.c\
		start.c\
		end.c\

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "compiling Philosophers..."
	@$(CC) $(CFLAGS) $(OBJS) -I $(LIB) -o $(NAME)
	@echo "Philosophers compiled!!"

clean:
	@echo "cleaning everything..."
	@rm -f $(OBJS)
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re