# Project

NAME := philo
OS := $(shell uname)

# Necessities

CC := cc
CFLAGS = -Wall -Wextra -Werror -pedantic -g3

Dar = Darwin

Lin = Linux

ifeq (${OS}, ${Dar})
	CFLAGS += -lpthread
else ifeq (${OS}, ${Lin})
	CFLAGS += -pthread
else
    $(error Idk, man. Doesn't look like something I was BUILT to deal with ;3)
endif

#CFLAGS += -fsanitize=address,undefined
#CFLAGS += -fsanitize=thread,undefined

SRCS := main.c ft_atoi.c utils.c simulation.c init.c destroy.c arbiter.c
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
