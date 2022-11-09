#include "../inc/cub3d.h"

void	start_game(t_game *game)
{
	mlx_loop(game->mlx.id);
}

int	init_game(t_map *map)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	game.map = map;
	init_input_and_scene_funcs(&game);
	game.scene.scene_func = (void *)pac_game_scene;
	game.scene.parameter = &game;
	set_game_input_mode(&game, START_MODE);
	game.mlx.id = mlx_init();
	if (!game.mlx.id)
		error_exit(&game, 1, "Game initialization error: MLX initialization");
	initialize_start_game_variables(&game);
	initialize_game_data(&game);
	start_game(&game);
	return (1);
}
