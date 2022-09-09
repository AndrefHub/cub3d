NAME    = cub3d
CC      = gcc
FLAGS	= -Wall -Wextra -Werror -o2 -g
LFLAGS	= -Llibft -lft 
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
			game_sound.c\
			start_game.c \
			time_funcs.c
SRCS	= $(addprefix $(SRCDIR), $(SRCFILE))
OBJDIR	= obj/
OBJFILE = $(SRCFILE:.c=.o)
OBJBNS	= $(addprefix $(OBJDIR), $(BONUS:.c=.o))
OBJS	= $(addprefix $(OBJDIR), $(OBJFILE))
RM      = rm -rf
LIBHDR  = libft/libft.h
INCDIR  = inc/
CUBHDR  = $(addprefix $(INCDIR), cub3d.h)
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

DEFINES	= -DASSETS_PATH='"'$(GOINFRE)'"'

all: download_assets $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(MSHHDR)
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@ -include $(LIBHDR) -include $(CUBHDR) $(DEFINES)
	@printf "\033[1;36m/\033[0m"

$(NAME): $(OBJS) $(OBJMAIN) $(MSHHDR)
	@echo
	@echo "\033[1;33m"$(NAME) "objs is up to date."'\033[0m'
	@make -C libft
	@make -C $(MLX)
	@make -C cute_sound
	@$(CC) $(FLAGS) $(OBJS) $(SNDLIB) $(OBJMAIN) $(LFLAGS) $(MLXFLAGS) $(DEFINES) -o $(NAME)
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

download_assets:
#	/bin/bash assets.sh $(GOINFRE)

.PHONY: all clean fclean re bonus
