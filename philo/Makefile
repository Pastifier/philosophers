# Project

NAME := philo

# Necessities

CC := cc
CFLAGS := -Wall -Wextra -Werror -pedantic -lpthread -g3

SRCS := main.c ft_atoi.c utils.c simulation.c init.c
INCLUDES := philo.h


# Rules

all : $(NAME)

$(NAME) : $(SRCS) $(INCLUDES)
	$(CC) $(CFLAGS) -I. $(SRCS) -o $@

clean :

fclean :
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
