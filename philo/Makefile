NAME	= philo
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -g3 -pthread
SRC	+= src/main.c
SRC	+= src/actions.c
SRC	+= src/actions_helper.c
SRC	+= src/brain.c
SRC	+= src/ft.c
SRC	+= src/init.c
SRC	+= src/parse.c
SRC	+= src/simulation_helper.c
SRC	+= src/threads_handler.c
OBJ	= $(SRC:%.c=%.o)
PATH_HEADERS += include/
HEADERS	+=	$(PATH_HEADERS)philo.h
HEADERS	+=	$(PATH_HEADERS)defines.h

%.o:	%.c	$(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(PATH_HEADERS:%=-I%)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(PATH_HEADERS:%=-I%)

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean	all

.PHONY:	all clean fclean re

