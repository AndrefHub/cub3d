NAME    = cub3d
CC      = gcc
FLAGS	= -Wall -Wextra -Werror -o2 -g
LFLAGS	= -Llibft -lft 
# SRCDIR	= src_bonus/
# SRCFILE	=	border_checking.c \
# 			border_checking_utils.c \
# 			check_file.c \
# 			controller.c \
# 			demo_utils.c \
# 			draw_map.c \
# 			drawing.c \
# 			ft_utils.c \
# 			input_manip.c \
# 			parsing.c \
# 			start_game.c \
# 			vector_utils.c \
# 			ray_casting.c \
# 			hooks.c
SRCDIR	= src_bonus/
SRCFILE	=	border_checking.c \
			border_checking_utils.c \
			check_file.c \
			controller.c \
			demo_utils.c \
			draw_map.c \
			drawing.c \
			free_game.c \
			ft_utils.c \
			hooks.c \
			input_manip.c \
			main.c \
			parsing.c \
			ray_casting.c \
			start_game.c \
			vector_utils.c
SRCS	= $(addprefix $(SRCDIR), $(SRCFILE))
OBJDIR	= obj/
OBJFILE = $(SRCFILE:.c=.o)
OBJBNS	= $(addprefix $(OBJDIR), $(BONUS:.c=.o))
OBJS	= $(addprefix $(OBJDIR), $(OBJFILE))
RM      = rm -rf
LIBHDR  = libft/libft.h
CUBHDR  = $(addprefix $(INCDIR), cub3d_bonus.h)
INCDIR  = inc/
SNDLIB  = cute_sound/cute_sound.o 

UNAME	= $(shell uname -s)
ifeq ($(UNAME), Darwin)
	MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
	MLX		= mlx
	SNDLIB	+= cute_sound/SDL2
endif
ifeq ($(UNAME), Linux)
	MLXFLAGS = -Lmlx_linux -lmlx -Imlx_linux -lXext -lX11 -lm -lz
	MLX		= mlx_linux
	SNDLIB	+= -lSDL2
endif

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(MSHHDR)
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@ -include $(LIBHDR) -include $(CUBHDR)
	@printf "\033[1;36m/\033[0m"

$(NAME): $(OBJS) $(OBJMAIN) $(MSHHDR)
	@echo
	@echo "\033[1;33m"$(NAME) "objs is up to date."'\033[0m'
	@make -C libft
	@make -C $(MLX)
	@make -C cute_sound
	@$(CC) $(FLAGS) $(OBJS) $(SNDLIB) $(OBJMAIN) $(LFLAGS) $(MLXFLAGS) -o $(NAME)
	@echo "\033[1;33m"$(NAME) "is up to date."'\033[0m'

clean:
	@$(RM) $(OBJDIR)
	@echo '\033[1;31m'$(NAME) "objs deleted."'\033[0m'

clean_proj_files: clean
	@$(RM) $(NAME)

fclean: clean_proj_files
	@make -C libft fclean
	@make -C $(MLX) clean
	@make -C cute_sound fclean
	@echo '\033[1;31m'$(NAME) "deleted."'\033[0m'

re: clean all

full_rebuild: fclean all

.PHONY: all clean fclean re bonus
