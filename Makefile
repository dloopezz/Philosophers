NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g -fsanitize=address
THREAD_DEBUG = -fsanitizer=thread -g

LIB = philo.h
#SRC_PATH = ./philo/

SRC =	philo.c\
		utils.c\
		start.c\
#SRCS = $(addprefix $(SRC_PATH), $(SRC))

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