NAME    = cub3d
CC      = gcc
FLAGS	= -Wall -Wextra -Werror -g
LFLAGS	= -L./libft -lft
MLXFLAGS	= -L./mlx -lmlx
SRCDIR	= src/
SRCFILE	= check_file.c ft_utils.c input_manip.c parsing.c parsing2.c
MAIN	= main.c
SRCS	= $(addprefix $(SRCDIR), $(SRCFILE))
OBJDIR	= obj/
OBJFILE = $(SRCFILE:.c=.o)
OBJMAIN = $(addprefix $(OBJDIR), $(MAIN:.c=.o))
OBJBNS	= $(addprefix $(OBJDIR), $(BONUS:.c=.o))
OBJS	= $(addprefix $(OBJDIR), $(OBJFILE))
RM      = rm -rf
LIBHDR  = libft/libft.h
CUBHDR  = cub3d.h

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(MSHHDR)
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@  -include $(LIBHDR) -include $(CUBHDR)
	@printf "\033[1;36m/\033[0m"

$(NAME): $(OBJS) $(OBJMAIN) $(MSHHDR)
	@echo
	@echo "\033[1;33m"$(NAME) "objs is up to date."'\033[0m'
	@make -C libft
	@make -C mlx
	@$(CC) $(FLAGS) $(OBJS) $(OBJMAIN) $(LFLAGS) $(MLXFLAGS) -o $(NAME)
	@echo "\033[1;33m"$(NAME) "is up to date."'\033[0m'

clean:
	@$(RM) $(OBJDIR)
	@echo '\033[1;31m'$(NAME) "objs deleted."'\033[0m'

fclean: clean
	@make -C libft fclean
	@make -C mlx clean
	@$(RM) $(NAME)
	@echo '\033[1;31m'$(NAME) "deleted."'\033[0m'

re: fclean all

.PHONY: all clean fclean re bonus
