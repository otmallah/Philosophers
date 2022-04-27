NAME = philo

NAME_B = checker

CC = gcc 


CFLAGS = -Wall -Werror -Wextra

AR = ar -rc

RM = @rm -f

FILES =  philo.c philo_utils.c  ft_usleep.c sec_philo_utils.c

# Colors
C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_GREEN = \033[1;32m
C_BLUE = \033[1;34m
C_L_BLUE = \033[1;34m
C_WHITE = \033[1;37m
C_RES = \033[0m


all : $(NAME)

$(NAME) : $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $(NAME) -fsanitize=address -g3
	@echo "$(C_GREEN)[LIBRARY CREATED!]$(C_RES)"

clean :
	$(RM) $(NAME)
	@echo "$(C_RED)[DELETED!]$(C_RES)"

fclean : clean
	$(RM) $(NAME) $(NAME_B)
	@echo "$(C_RED)[REMOVED!]$(C_RES)"


re : fclean all
