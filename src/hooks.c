/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:00 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:47:02 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	if (key == ESC_KEY)
		error_exit(game, 0, NULL);
	game->key.k[(short)(key + CHAR_OFFSET)] = true;
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
