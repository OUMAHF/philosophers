NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror 

RM = rm -f

SRC = main.c utils.c thread_creation.c routine_actions.c monitor_routine.c philo_routine.c init.c
OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
