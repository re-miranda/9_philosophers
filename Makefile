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

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(PATH_HEADERS:%=-I%)

%.o:	%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(PATH_HEADERS:%=-I%)

all:	$(NAME)

clean: all
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

val: all
	valgrind -s --log-fd=9 --tool=helgrind 9>memcheck.log ./philo 5 800 200 200 2

.PHONY:	all clean fclean re val

