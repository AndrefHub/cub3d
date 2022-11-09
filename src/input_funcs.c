#include "../inc/cub3d.h"

inline int	game_input_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
		pause_game(game);
	else
	{
		game->key.k[(short)(key + CHAR_OFFSET)] = true;
	}
	return (0);
}

inline int	username_input_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
		close_hook(game);
	if (key == BACKSPACE)
		game->player_lb_data->name[ft_strlen(game->player_lb_data->name) - 1]
			= '\0';
	else if (key == ENTER && ft_strlen(game->player_lb_data->name))
		update_leaderboard_file(game);
	else
		input_char(key, game->player_lb_data->name, game->macos_chars);
	return (0);
}

inline int	win_screen_mode(int key, t_game *game)
{
	if (key == ENTER)
		set_game_input_mode(game, LEADERBOARD_MODE);
	return (0);
}

inline int	pause_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
	{
		close_hook(game);
	}
	else if (key == DOWN_KEY)
	{
		game->pause.buttons[game->pause.index].selected = 0;
		game->pause.index = (game->pause.index + 1) % PAUSE_ENTRIES;
		game->pause.buttons[game->pause.index].selected = 1;
	}
	else if (key == UP_KEY)
	{
		game->pause.buttons[game->pause.index].selected = 0;
		game->pause.index = (game->pause.index + PAUSE_ENTRIES - 1)
			% PAUSE_ENTRIES;
		game->pause.buttons[game->pause.index].selected = 1;
	}
	return (0);
}

int	controls_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
	{
		set_game_input_mode(game, PAUSE_MODE);
		game->scene.scene_func = (void *)pause_game_scene;
	}
	return (0);
}	
