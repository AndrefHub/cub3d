cmake_minimum_required(VERSION 3.21)
project(cub3d C)

set(CMAKE_C_STANDARD 99)

if(APPLE)
    include_directories(AFTER "/opt/X11/include")
endif()
add_compile_definitions(ASSETS_PATH=".")
add_compile_options(-MMD -g -Ofast -march=native)
#add_compile_options(-MMD)

add_executable(cub3d
        src_bonus/border_checking.c
        src_bonus/check_file.c
        src_bonus/controller.c
        src_bonus/demo_utils.c
        src_bonus/draw_map.c
        src_bonus/drawing.c
        src_bonus/free_game.c
        src_bonus/ft_utils.c
        src_bonus/game_loop.c
        src_bonus/game_sound.c
        src_bonus/game_textures.c
        src_bonus/death_events.c
        src_bonus/vector_utils.c
        src_bonus/hooks.c
        src_bonus/input_manip.c
        src_bonus/main.c
        src_bonus/image_manip.c
        src_bonus/draw_hud.c
        src_bonus/player_eating.c
        src_bonus/enemy_actions.c
        src_bonus/is_checks.c
        src_bonus/find_objects.c
        src_bonus/init_utils.c
        src_bonus/input_mode.c
        src_bonus/enemy_astar.c
        src_bonus/downscale_image.c
        src_bonus/mlx_adapter.c
        src_bonus/parsing.c
        src_bonus/parsing_font.c
        src_bonus/parsing_textures.c
        src_bonus/parsing_utils.c
        src_bonus/player_controller.c
        src_bonus/player_movement.c
        src_bonus/put_text.c
        src_bonus/ray_casting.c
        src_bonus/draw_walls.c
        src_bonus/respawn.c
        src_bonus/vector_utils.c
        src_bonus/start_game.c
        src_bonus/time_funcs.c
        src_bonus/game_sound.c
        src_bonus/game_loop.c
        src_bonus/draw_ceil_floor.c
        src_bonus/enemy_move.c
        cute_sound/cute_sound.c src_bonus/draw_objects.c src_bonus/ft_lstsort.c)
#if ($ENV{USER} EQUAL "landreas")
    target_link_libraries(cub3d /Users/lsherry/42Course/cub3d/mlx/libmlx.a "-framework OpenGL" "-framework AppKit")
    target_link_libraries(cub3d /Users/lsherry/42Course/cub3d/libft/libft.a)
    target_link_libraries(cub3d /Users/lsherry/42Course/cub3d/cute_sound/SDL/SDL2)
#else()
#    target_link_libraries(cub3d /Users/lsherry/42Course/cub3d/mlx/libmlx.a "-framework OpenGL" "-framework AppKit")
#    target_link_librraries(cub3d /Users/lsherry/42Course/cub3d/libft/libft.a)
#    target_link_libraries(cub3d /Users/lsherry/42Course/cub3d/cute_sound/SDL2)
#endif()
