# Project

NAME := philo

# Necessities

CC := cc
CFLAGS := -Wall -Wextra -Werror -pedantic -lpthread

SRCS := main.c
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
