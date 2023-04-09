/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:51 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 15:07:06 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

inline int	game_input_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
		pause_game(game);
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
		close_hook(game);
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
		set_game_input_mode(game, game->index_before_controls);
	}
	return (0);
}	
