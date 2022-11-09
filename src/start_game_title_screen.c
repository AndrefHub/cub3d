#include "../inc/cub3d.h"

void	initialize_game_hud(t_game *game)
{
	if (game->mlx.win_size.x >= 2560 && game->mlx.win_size.y >= 1440)
		game->mlx.game_size = (t_vector){2560, 1440};
	else if (game->mlx.win_size.x >= 1920 && game->mlx.win_size.y >= 1080)
		game->mlx.game_size = (t_vector){1920, 1080};
	else if (game->mlx.win_size.x >= 1280 && game->mlx.win_size.y >= 720)
		game->mlx.game_size = (t_vector){1280, 720};
	game->hud_img = initialize_img(&game->hud_img, game->mlx.id,
			game->mlx.win_size.x, game->mlx.win_size.y);
}

void	initialize_game_parameters(t_game *game)
{
	get_screen_size(game->mlx.id, &game->mlx.win_size.x, &game->mlx.win_size.y);
	game->mlx.window = mlx_new_window(game->mlx.id,
			game->mlx.win_size.x, game->mlx.win_size.y, PROJ_NAME);
	initialize_game_hud(game);
	game->key.mouse = true;
	game->show_map = false;
	game->z_offset = 0;
	game->grid = game->map->map;
	game->img = initialize_img(&game->img, game->mlx.id, game->mlx.game_size.x,
			game->mlx.game_size.y);
	game->hud_img = initialize_img(&game->hud_img, game->mlx.id,
			game->mlx.win_size.x, game->mlx.win_size.y);
	game->map->map_tile_size = ft_min
		(game->map->img.size.x / game->map->map_size.x,
		game->map->img.size.y / game->map->map_size.y);
	game->col = malloc(sizeof(*game->col) * game->img.size.x);
	ft_memset(game->key.k, 0, 512);
	if (game->col == NULL)
		error_exit(game, 0, NULL);
}

void	initialize_mlx_parameters(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx.id);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask,
		key_hook_press, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask,
		key_hook_release, game);
	mlx_hook(game->mlx.window, ButtonPress, ButtonPressMask,
		mouse_hook_press, game);
	mlx_hook(game->mlx.window, ButtonRelease, ButtonReleaseMask,
		mouse_hook_release, game);
	mlx_hook(game->mlx.window, DestroyNotify, StructureNotifyMask,
		close_hook, game);
	mlx_loop_hook(game->mlx.id, game_loop, &game->scene);
	mouse_move(game->mlx.id, game->mlx.window, game->mlx.win_size.x / 2,
		game->mlx.win_size.y / 2);
}

void	initialize_start_game_variables(t_game *game)
{
	initialize_game_parameters(game);
	initialize_mlx_parameters(game);
}
