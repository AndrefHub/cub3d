NAME    = cute_sound.o
CC      = gcc
FLAGS	= -Ofast -march=native  
MAIN	= cute_sound.c
RM      = rm -rf
HEADER  = cute_sound.h

all: $(NAME)

$(NAME): $(HEADER) $(MAIN)
	@$(CC) $(FLAGS) -c $(MAIN) -o $(NAME)
	@echo "\033[1;33m"$(NAME) "is up to date."'\033[0m'

fclean:
	@$(RM) $(NAME)
	@echo '\033[1;31m'$(NAME) "deleted."'\033[0m'

re: fclean all

.PHONY: all clean fclean re bonus
