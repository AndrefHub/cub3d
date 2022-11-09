/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:46:54 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:46:56 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 1
void	pac_game_scene(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	fill_ceiling_color(&game->img, game->map->c, 0);
	fill_floor_color(&game->img, game->map->f, 0);
	player_controll(game);
	cast_rays(game);
	draw_walls(game);
	draw_aim(game);
	put_frame(game);
}
