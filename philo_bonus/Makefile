NAME	= philo_bonus
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -g3 -pthread
SRC	+= src_bonus/main_bonus.c
SRC	+= src_bonus/actions_bonus.c
SRC	+= src_bonus/actions_helper_bonus.c
SRC	+= src_bonus/brain_bonus.c
SRC	+= src_bonus/ft_bonus.c
SRC	+= src_bonus/init_bonus.c
SRC	+= src_bonus/parse_bonus.c
SRC	+= src_bonus/simulation_helper_bonus.c
SRC	+= src_bonus/threads_handler_bonus.c
OBJ	= $(SRC:%.c=%.o)
PATH_HEADERS += include_bonus/
HEADERS	+=	$(PATH_HEADERS)philo_bonus.h
HEADERS	+=	$(PATH_HEADERS)defines_bonus.h

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

val: all
	-valgrind -s --log-fd=9 --tool=helgrind 9>memcheck.log ./philo_bonus 5 -2147483649 200 
	-valgrind -s --log-fd=9 --tool=helgrind 9>>memcheck.log ./philo_bonus 5 2147483647 20o 200 2
	-valgrind -s --log-fd=9 --tool=helgrind 9>>memcheck.log ./philo_bonus 5 2147483648 200 200 2
	-valgrind -s --log-fd=9 --tool=helgrind 9>>memcheck.log ./philo_bonus 5 -2147483649 200 200 2
	-valgrind -s --log-fd=9 --tool=helgrind 9>>memcheck.log ./philo_bonus 5 -2147483648 200 200 2
	valgrind -s --log-fd=9 --tool=helgrind 9>>memcheck.log ./philo_bonus 5 2147483647 200 200 2
	valgrind -s --log-fd=9 --tool=helgrind 9>>memcheck.log ./philo_bonus 5 800 200 200 2
	valgrind -s --log-fd=9 --tool=helgrind 9>>memcheck.log ./philo_bonus 4 410 200 200 180
	valgrind -s --log-fd=9 --tool=helgrind 9>>memcheck.log ./philo_bonus 4 130 60 60 180

leak: all
	-valgrind -s --log-fd=9 --leak-check=full --show-leak-kinds=all 9>memcheck.log ./philo_bonus 5 -2147483649 200 
	-valgrind -s --log-fd=9 --leak-check=full --show-leak-kinds=all 9>>memcheck.log ./philo_bonus 5 2147483647 20o 200 2
	-valgrind -s --log-fd=9 --leak-check=full --show-leak-kinds=all 9>>memcheck.log ./philo_bonus 5 2147483648 200 200 2
	-valgrind -s --log-fd=9 --leak-check=full --show-leak-kinds=all 9>>memcheck.log ./philo_bonus 5 -2147483649 200 200 2
	-valgrind -s --log-fd=9 --leak-check=full --show-leak-kinds=all 9>>memcheck.log ./philo_bonus 5 -2147483648 200 200 2
	valgrind -s --log-fd=9 --leak-check=full --show-leak-kinds=all 9>>memcheck.log ./philo_bonus 5 2147483647 200 200 2
	valgrind -s --log-fd=9 --leak-check=full --show-leak-kinds=all 9>>memcheck.log ./philo_bonus 5 800 200 200 2
	valgrind -s --log-fd=9 --leak-check=full --show-leak-kinds=all 9>>memcheck.log ./philo_bonus 4 410 200 200 180
	valgrind -s --log-fd=9 --leak-check=full --show-leak-kinds=all 9>>memcheck.log ./philo_bonus 4 130 60 60 180

.PHONY:	all clean fclean re val

