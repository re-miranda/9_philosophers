NAME	= philo
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -g3 -pthread
SRC	+= src/main.c
SRC	+= src/ft.c
SRC	+= src/parse.c
OBJ	= $(SRC:%.c=%.o)
PATH_HEADERS += include/

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(PATH_HEADERS:%=-I%)

src/%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(PATH_HEADERS:%=-I%)

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

