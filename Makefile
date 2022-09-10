NAME    = cub3d
CC      = clang
FLAGS	= -Wall -Wextra -Werror -g -MMD -Ofast -march=native
LFLAGS	= -Llibft -lft
###
SRCDIR	= src/
SRCFILE	=	border_checking.c \
			check_file.c \
			controller.c \
			demo_utils.c \
			draw_map.c \
			game_textures.c \
			drawing.c \
			free_game.c \
			ft_utils.c \
			hooks.c \
			input_manip.c \
			main.c \
			parsing.c \
			ray_casting.c \
			mlx_adapter.c \
			start_game.c \
			time_funcs.c
SRCS	= $(addprefix $(SRCDIR), $(SRCFILE))
OBJDIR	= obj/
OBJFILE = $(SRCFILE:.c=.o)
OBJS	= $(addprefix $(OBJDIR), $(OBJFILE))
###
SRC_BONUSDIR	= src_bonus/
SRC_BONUSFILE	= main.c \
					parsing.c \
					check_file.c \
					ft_utils.c \
					input_manip.c \
					border_checking.c \
					start_game.c \
					game_sound.c\
					game_textures.c \
					hooks.c \
					mlx_adapter.c \
					game_loop.c \
					ray_casting.c \
					controller.c \
					player_controller.c \
					player_movement.c \
					drawing.c \
					draw_map.c \
					demo_utils.c \
					free_game.c \
					vector_utils.c \
					time_funcs.c
SRCS_BONUS	= $(addprefix $(SRC_BONUSDIR), $(SRC_BONUSFILE))
OBJ_BONUSDIR	= obj_bonus/
OBJ_BONUSFILE = $(SRC_BONUSFILE:.c=.o)
OBJS_BONUS	= $(addprefix $(OBJ_BONUSDIR), $(OBJ_BONUSFILE))
###
RM      = rm -rf
LIBHDR  = libft/libft.h
INCDIR  = inc/
CUBHDR  = $(addprefix $(INCDIR), cub3d.h)
###
INC_BONUSDIR = inc_bonus/
CUB_BONUSHDR  = $(addprefix $(INC_BONUSDIR), cub3d_bonus.h)
SNDLIB  = cute_sound/cute_sound.o

UNAME	= $(shell uname -s)

ifeq ($(UNAME), Darwin)
	MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
	MLX		= mlx
	SNDLIB	+= cute_sound/SDL2
	GOINFRE	= $(HOME)/goinfre
endif

ifeq ($(UNAME), Linux)
	MLXFLAGS = -Lmlx_linux -lmlx -Imlx_linux -lXext -lX11 -lm -lz
	MLX		= mlx_linux
	SNDLIB	+= -lSDL2
	GOINFRE = .
endif

ifneq ($(shell [ -d $(GOINFRE) ]; echo $?), 0)
	GOINFRE = .
endif

DEFINES	= -DASSETS_PATH='"'$(GOINFRE)'"'


all: download_assets $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(MSHHDR)
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@ -include $(LIBHDR) -include $(CUBHDR) $(DEFINES)
	@printf "\033[1;36m/\033[0m"

$(OBJ_BONUSDIR)%.o: $(SRC_BONUSDIR)%.c $(MSHHDR)
	@mkdir -p $(OBJ_BONUSDIR)
	@$(CC) $(FLAGS) -c $< -o $@ -include $(LIBHDR) -include $(CUB_BONUSHDR) $(DEFINES)
	@printf "\033[1;36m/\033[0m"

$(NAME): $(OBJS) $(MSHHDR)
	@echo
	@echo "\033[1;33m"$(NAME) "objs is up to date."'\033[0m'
	@make -C libft
	@make -C $(MLX)
	@$(CC) $(FLAGS) $(OBJS) $(LFLAGS) $(MLXFLAGS) $(DEFINES) -o $(NAME)
	@echo "\033[1;33m"$(NAME) "is up to date."'\033[0m'

bonus: download_assets  $(OBJS_BONUS)
	@echo
	@echo "\033[1;33m"$(NAME)"_bonus" "objs is up to date."'\033[0m'
	@make -C libft
	@make -C $(MLX)
	@make -C cute_sound
	@$(CC) $(FLAGS) $(OBJS_BONUS) $(SNDLIB) $(LFLAGS) $(MLXFLAGS) $(DEFINES) -o $(NAME)
	@echo "\033[1;33m"$(NAME)"_bonus" "is up to date."'\033[0m'

clean:
	@$(RM) $(OBJDIR)
	@echo '\033[1;31m'$(NAME) "objs deleted."'\033[0m'
	@$(RM) $(OBJ_BONUSDIR)
	@echo '\033[1;31m'$(NAME)"_bonus" "objs deleted."'\033[0m'

clean_proj_files: clean
	@$(RM) $(NAME)

fclean: clean_proj_files
	@make -C libft fclean
	@make -C $(MLX) clean
	@make -C cute_sound fclean
	@echo '\033[1;31m'$(NAME) "deleted."'\033[0m'

re: clean all

full_rebuild: fclean all

download_assets:
	@/bin/bash assets.sh $(GOINFRE)

.PHONY: all clean fclean re bonus
