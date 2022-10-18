#include "../inc_bonus/cub3d_bonus.h"

bool	key_pressed(t_game *game, int key)
{
	return (game->key.k[(short)(key + CHAR_OFFSET)]);
}

int	close_hook(t_game *game)
{
	mlx_clear_window(game->mlx.id, game->mlx.window);
	mlx_destroy_window(game->mlx.id, game->mlx.window);
	error_exit(game, 0, NULL);
	return (0);
}

void	pause_game(t_game *game)
{
	
}

int	key_hook_press(int key, t_game *game)
{
	if (!(0 <= (short)(key + CHAR_OFFSET) && (short)(key + CHAR_OFFSET) < 512))
		return (1);
	if (key == ESC_KEY)
		close_hook(game);
	if (game->input_mode == WIN_SCREEN_MODE && key == ENTER)
		--game->input_mode;
	else if (game->input_mode == INPUT_MODE)
		input_mode(key, game);
	else
	{
		if (key == M_KEY)
		{
			game->show_map = !game->show_map;
			return (0);
		}
		if (key == E_KEY)
			open_door(game);
		game->key.k[(short)(key + CHAR_OFFSET)] = true;
	}
	return (0);
}

int	key_hook_release(int key, t_game *game)
{
	if (!(0 <= (short)(key + CHAR_OFFSET) && (short)(key + CHAR_OFFSET) < 512))
		return (1);
	game->key.k[(short)(key + CHAR_OFFSET)] = false;
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