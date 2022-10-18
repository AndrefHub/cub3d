#include "../inc_bonus/cub3d_bonus.h"

// game->input_mode = GAME_MODE (0) //
inline int	game_input_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
	{
		game->input_mode = PAUSE_MODE;
		game->scene.scene_func = (void *)pause_game_scene;
	}
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

// game->input_mode = INPUT_MODE (1) //
inline int	username_input_mode(int key, t_game *game)
{
	if (key == ESC_KEY && ft_strlen(game->player_lb_data->name))
		close_hook(game);
	if (key == BACKSPACE) // Backspace
		game->player_lb_data->name[ft_strlen(game->player_lb_data->name) - 1]
			= '\0';
	else if (key == ENTER) // Enter, to add confirm action
		update_leaderboard_file(game);
	else
		input_char(key, game->player_lb_data->name, game->macos_chars);
	return (0);
}

// game->input_mode = WIN_SCREEN_MODE (2) //
inline int	win_screen_mode(int key, t_game *game)
{
	if (key == ENTER)
		game->input_mode = INPUT_MODE;
	return (0);
}

// game->input_mode = PAUSE_MODE (3) //
inline int	pause_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
	{
		close_hook(game);
	}
	else if (key == DOWN_KEY)
	{
		game->pause.index = (game->pause.index + 1) % PAUSE_ENTRIES;
	}
	else if (key == UP_KEY)
	{
		game->pause.index = (game->pause.index - 1) % PAUSE_ENTRIES;
	}
	else if (key == ENTER)
	{
		game->input_mode = GAME_MODE;
		game->scene.scene_func = (void *)pac_game_scene;
	}
	return (0);
}	
