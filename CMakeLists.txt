cmake_minimum_required(VERSION 3.21)
project(cub3d C)

set(CMAKE_C_STANDARD 99)

add_executable(cub3d
        src/border_checking.c
        src/check_file.c
        src/ft_utils.c
        src/input_manip.c
        src/main.c
        src/parsing.c
        src/start_game.c)

target_link_libraries(cub3d /Users/lsherry/42Course/cub3d/mlx/libmlx.a "-framework OpenGL" "-framework AppKit")
target_link_libraries(cub3d /Users/lsherry/42Course/cub3d/libft/libft.a)