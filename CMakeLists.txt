cmake_minimum_required(VERSION 3.21)
project(cub3d C)

set(CMAKE_C_STANDARD 99)

add_executable()

target_link_libraries(cub3d /Users/lsherry/42Course/so_long/mlx/libmlx.a "-framework OpenGL" "-framework AppKit")
target_link_libraries(cub3d /Users/lsherry/42Course/so_long/libft/libft.a)