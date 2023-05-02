NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g -fsanitize=address

LIB = philo.h
#SRC_PATH = ./philo/

SRC =	philo.c\

#SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "compiling philo..."
	@$(CC) $(CFLAGS) $(OBJS) -I $(LIB) -o $(NAME)
	@echo "philo compiled!!"

clean:
	@echo "cleaning everything..."
	@rm -f $(OBJS)
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re