/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:20 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:50:22 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	pause_game(t_game *game)
{
	change_all_enemies_cry_paused(game, 1);
	mouse_show(game->mlx.id, game->mlx.window);
	set_game_input_mode(game, PAUSE_MODE);
	return (0);
}

int	resume_game(t_game *game)
{
	change_all_enemies_cry_paused(game, 0);
	mouse_hide(game->mlx.id, game->mlx.window);
	set_game_input_mode(game, GAME_MODE);
	mouse_move(game->mlx.id, game->mlx.window,
		game->mlx.win_size.x / 2, game->mlx.win_size.y / 2);
	return (0);
}

inline int	start_input_mode(int key, t_game *game)
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
