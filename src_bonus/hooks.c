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

int	key_hook_press(int key, t_game *game)
{
	if (!(0 <= (short)(key + CHAR_OFFSET) && (short)(key + CHAR_OFFSET) < 512))
		return (1);
	game->input_funcs[game->input_mode](key, game);
	game->key.k[(short)(key + CHAR_OFFSET)] = true;
	return (0);
}

int	key_hook_release(int key, t_game *game)
{
	if (!(0 <= (short)(key + CHAR_OFFSET) && (short)(key + CHAR_OFFSET) < 512))
		return (1);
	game->key.k[(short)(key + CHAR_OFFSET)] = false;
	if ((game->input_mode == PAUSE_MODE || game->input_mode == START_MODE)
		&& key == ENTER)
	{
		game->pause.buttons[game->pause.index].released = 1;
		game->pause.buttons[game->pause.index].pressed = 0;
	}
	return (0);
}

int	mouse_hook_press(int button, int x, int y, t_game *game)
{
	if ((unsigned)button >= sizeof(game->key.m))
		return (1);
	game->key.m[button] = true;
	if (game->input_mode == PAUSE_MODE || game->input_mode == START_MODE)
	{
		game->pause.buttons[game->pause.index].pressed = 1;
	}
	return (0);
	(void) x;
	(void) y;
}

int	mouse_hook_release(int button, int x, int y, t_game *game)
{
	if ((unsigned)button >= sizeof(game->key.m))
		return (1);
	game->key.m[button] = false;
	if (game->input_mode == PAUSE_MODE || game->input_mode == START_MODE)
	{
		game->pause.buttons[game->pause.index].released = 1;
		game->pause.buttons[game->pause.index].pressed = 0;
	}
	return (0);
	(void) x;
	(void) y;
}
