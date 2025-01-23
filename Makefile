NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread 
RM = rm -f

SRC = philo.c helper.c parsing.c utils/number.c utils/string.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $@

%.o : %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: clean
