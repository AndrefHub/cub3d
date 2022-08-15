#include "../inc/cub3d.h"

bool	key_pressed(t_game *game, int key)
{
	return (game->key.k[key]);
}

int	close_hook(t_game *game)
{
	mlx_clear_window(game->mlx.id, game->mlx.window);
	mlx_destroy_window(game->mlx.id, game->mlx.window);
	exit(0);
	return (0);
}

int	key_hook_press(int key, t_game *game)
{
	if (key >= (int) sizeof(game->key) || key < -256)
		return (1);
	if (key == ESC_KEY)
		close_hook(game);
	if (key == M_KEY)
	{
		game->show_map = !game->show_map;
		return (0);
	}
	game->key.k[key] = true;
	return (0);
}

int	key_hook_release(int key, t_game *game)
{
	if (key >= (int) sizeof(game->key) || key < -256)
		return (1);
	game->key.k[key] = false;
	return (0);
}

int	mouse_hook_press(int button, int x, int y, t_game *game)
{
	if ((unsigned)button >= sizeof(game->key.m))
		return (1);
	game->key.m[button] = true;
	return (0);
	(void) x;
	(void) y;
}

int	mouse_hook_release(int button, int x, int y, t_game *game)
{
	if ((unsigned)button >= sizeof(game->key.m))
		return (1);
	game->key.m[button] = false;
	return (0);
	(void) x;
	(void) y;
}