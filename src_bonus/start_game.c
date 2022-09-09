#include "../inc_bonus/cub3d_bonus.h"

void	initialize_mlx_parameters(t_game *game)
{
	mouse_hide(game->mlx.id, game->mlx.window);
	mlx_do_key_autorepeatoff(game->mlx.id);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask, key_hook_press, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask, key_hook_release, game);
	mlx_hook(game->mlx.window, ButtonPress, ButtonPressMask, mouse_hook_press, game);
	mlx_hook(game->mlx.window, ButtonRelease, ButtonReleaseMask, mouse_hook_release, game);
	mlx_hook(game->mlx.window, DestroyNotify, StructureNotifyMask, close_hook, game);
	mlx_loop_hook(game->mlx.id, game_loop, game);
}

void	initialize_player(t_game *game)
{
	game->player.pos = (t_fvector) {(float )game->map->player_coords.x
		* MAP_GRID_SIZE + MAP_GRID_SIZE / 2,
		(float )(game->map->player_coords.y - 1)
		* MAP_GRID_SIZE + MAP_GRID_SIZE / 2};
	game->player.angle = game->map->player_orient;
	game->player.delta.x = cosf(game->player.angle) * 5;
	game->player.delta.y = sinf(game->player.angle) * 5;
}

void	initialize_game_parameters(t_game *game)
{
	game->mlx.window = mlx_new_window(game->mlx.id,
		WIN_WIDTH, WIN_HEIGHT, PROJ_NAME);
	initialize_player(game);
	game->key.mouse = true;
	game->show_map = false;
	game->grid = game->map->map;
	game->img = initialize_img(&game->img, game->mlx.id, WIN_WIDTH, WIN_HEIGHT);
	game->map->img = initialize_img(&game->map->img, game->mlx.id,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
	game->map->map_tile_size = ft_min(game->map->img.size.x /
		game->map->map_size.x, game->map->img.size.y / game->map->map_size.y);
	game->column = malloc(sizeof(*game->column) * game->img.size.x);
	ft_memset(game->key.k, 0, 512);
	if (game->column == NULL)
		error_exit(game, 0, NULL);
}

void	start_game(t_game *game)
{
	init_time(game);
	cs_play_sound(game->audio.ctx, game->audio.song.def);
	wait_milliseconds(200);
	mlx_loop(game->mlx.id);
}

int	game(t_map *map)
{
	t_game	game;

	game.map = map;
	game.mlx.id = mlx_init();
	if (!game.mlx.id)
		error_exit(&game, 1, "Game initialization error: MLX initialization");
	init_main_game_sound_theme(&game, map->sounds[0]);
	set_game_events_sounds(&game.audio, map->sounds[1]);
	initialize_game_parameters(&game);
	initialize_sprites(&game, MAX_ENTITIES, (t_texture *)game.map->entity);
	initialize_sprites(&game, MAX_WALL_CHARS, (t_texture *)game.map->walls);
	initialize_mlx_parameters(&game);
	start_game(&game);
	return (1);
}