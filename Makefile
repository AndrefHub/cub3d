SHELL	= /bin/bash
MAKEFLAGS += --silent

NAME    = cub3d
#CC      = clang
CC      = gcc
# FLAGS	= -Wall -Wextra -Werror -g -O0 -fsanitize=address
FLAGS	= -Wall -Wextra -Werror -g -Ofast -march=native 
LFLAGS	= -Llibft -lft
###
SRCDIR	= src/
SRCFILE	=	border_checking.c \
			calculate_columns.c \
			cast_rays.c \
			check_file.c \
			demo_utils.c \
			draw_walls.c \
			drawing.c \
			drawing_utils.c \
			find_objects.c \
			ft_utils.c \
			ft_utils_game.c \
			game_loop.c \
			game_scenes.c \
			game_textures.c \
			get_screen_size.c \
			hooks.c \
			input_manip.c \
			is_checks.c \
			key_pressed.c \
			main.c \
			mlx_adapter_mouse_position.c \
			mlx_adapter_mouse_visibility.c \
			parsing.c \
			parsing_textures.c \
			parsing_utils.c \
			player_controller.c \
			player_movement.c \
			start_game.c \
			start_game_game_data.c \
			start_game_title_screen.c \
			vector_utils.c
SRCS	= $(addprefix $(SRCDIR), $(SRCFILE))
OBJDIR	= obj/
OBJFILE = $(SRCFILE:.c=.o)
OBJS	= $(addprefix $(OBJDIR), $(OBJFILE))
###
SRC_BONUSDIR	= src_bonus/
SRC_BONUSFILE	=	after_death_anim.c \
					border_checking.c \
					button_actions.c \
					button_core_funcs.c \
					button_selected.c \
					calculate_columns.c \
					cast_rays.c \
					check_file.c \
					controller.c \
					demo_utils.c \
					downscale_image.c \
					draw_ceil_floor.c \
					draw_hud.c \
					draw_map.c \
					draw_objects.c \
					draw_objects_utils.c \
					draw_walls.c \
					drawing.c \
					drawing_utils.c \
					end_game_funcs.c \
					end_game_utils.c \
					enemy_actions.c \
					enemy_actions_utils.c \
					enemy_astar.c \
					enemy_astar_utils.c \
					enemy_move.c \
					file_parser.c \
					find_objects.c \
					free_game.c \
					ft_lstsort.c \
					ft_utils.c \
					ft_utils_game.c \
					game_loop.c \
					game_scenes.c \
					game_scenes_utils.c \
					game_sound.c \
					game_textures.c \
					get_screen_size.c \
					hooks.c \
					image_manip.c \
					init_hud.c \
					input_char.c \
					input_funcs.c \
					input_manip.c \
					is_checks.c \
					key_pressed.c \
					leaderboard_funcs.c \
					main.c \
					mlx_adapter_mouse_position.c \
					mlx_adapter_mouse_visibility.c \
					parsing.c \
					parsing_font.c \
					parsing_textures.c \
					parsing_utils.c \
					pause_game.c \
					pause_menu.c \
					player_controller.c \
					player_eating.c \
					player_movement.c \
					put_text.c \
					respawn.c \
					set_game_audio_input_mode.c \
					start_game.c \
					start_game_buttons.c \
					start_game_game_data.c \
					start_game_title_screen.c \
					time_funcs.c \
					vector_utils.c

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
CUB_BONUSINC = inc_bonus/constants_bonus.h inc_bonus/cub3d_bonus.h inc_bonus/prototypes.h
SNDLIB  = cute_sound/cute_sound.o
LBFOLDER  = .lb

UNAME	= $(shell uname -s)

ifeq ($(UNAME), Darwin)
	MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
	MLX		= mlx
	SNDLIB	+= cute_sound/SDL/SDL2
	ECHO = echo
endif

ifeq ($(UNAME), Linux)
	MLXFLAGS = -Lmlx_linux -lmlx -Imlx_linux -lXext -lX11 -lm -lz
	MLX		= mlx_linux
	SNDLIB	+= -lSDL2
	GOINFRE = .
	ECHO = echo -e
endif

# BUILT_COUNT := 0

N := x
C = $(words $N)$(eval N := x $N)

# ifeq
FILES_COUNT := $(words $(SRCS_BONUS))

# bonus: T := $(shell $(MAKE) -n bonus_in $(MAKECMDGOALS) | grep -c "#   [0-9]")
# FILES_COUNT = $(shell (( ($(FILES_COUNT) - 8) / 3 )))

#ifeq ($(shell [ -d $(GOINFRE) ]; echo -e $?), 1) #TODO: it is doesn't work at school computer
#	GOINFRE = .
#endif

all: download_assets $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(CUB_HDR)
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@ -include $(LIBHDR) -include $(CUBHDR) $(DEFINES)
	@printf "\033[1;46m/\033[0m"

$(OBJ_BONUSDIR)%.o: $(SRC_BONUSDIR)%.c $(CUB_BONUSHDR) $(CUB_BONUSINC)
	@mkdir -p $(OBJ_BONUSDIR)
	@$(CC) $(FLAGS) -c $< -o $@ -include $(LIBHDR) -include $(CUB_BONUSHDR) $(DEFINES)
	@printf "\r"
	$(eval FILES_COMPILED := $(C))
	$(eval FILES_LEFT := $(shell expr $(FILES_COUNT) - $(FILES_COMPILED) + 1))
	printf '%0.s\033[0;46m \033[0m' {1..$(FILES_COMPILED)}
	printf '%0.s ' {1..$(FILES_LEFT)}
	# echo /$(FILES_COMPILED)
	echo -n '[' "$(FILES_COMPILED)/$(FILES_COUNT)" '] '

$(NAME): $(OBJS)
	@echo
	@echo -e "\033[1;33m"$(NAME) "objs are up to date."'\033[0m'
	@make -C libft
	@make -C $(MLX)
	@$(CC) $(FLAGS) $(OBJS) $(LFLAGS) $(MLXFLAGS) $(DEFINES) -o $(NAME)
	@echo -e "\033[1;43m"$(NAME) "is up to date."'\033[0m'

bonus: bonus_in ;

bonus_in: download_assets $(OBJS_BONUS)
	@mkdir -p $(LBFOLDER)
	@echo
	@echo -e "\033[1;33m"$(NAME)"_bonus" "objs are up to date."'\033[0m'
	@make -C libft
	@make -C $(MLX)
	@make -C cute_sound
	@$(CC) $(FLAGS) $(OBJS_BONUS) $(SNDLIB) $(LFLAGS) $(MLXFLAGS) $(DEFINES) -o $(NAME)
	@echo -e "\033[1;33m"$(NAME)"_bonus" "is up to date."'\033[0m'

clean:
	@$(RM) $(OBJDIR)
	@echo -e '\033[1;31m'$(NAME) "objs deleted."'\033[0m'
	@$(RM) $(OBJ_BONUSDIR)
	@echo -e '\033[1;31m'$(NAME)"_bonus" "objs deleted."'\033[0m'

clean_proj_files: clean
	@$(RM) $(NAME)

fclean: clean_proj_files
	@make -C libft fclean
	@make -C $(MLX) clean
	@make -C cute_sound fclean
	@echo -e '\033[1;31m'$(NAME) "deleted."'\033[0m'

re: clean bonus

full_rebuild: fclean all

download_assets:
	@/bin/bash scripts/assets.sh $(GOINFRE)

.PHONY: all clean fclean re bonus bonus_in
