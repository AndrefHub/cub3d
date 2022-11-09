/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:39 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:47:41 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	get_interception(t_game *game, t_fvector ray_dir, int i)
{
	t_ray	ray;

	ray = ray_initialize(game, ray_dir);
	game->col[i].dist = interception_distance(game, &ray);
	initialize_columns(game, &ray, i,
		calculate_angle((t_fvector){1, 0}, ray_dir));
}

void	cast_rays(t_game *game)
{
	int			i;
	t_fvector	ray;
	float		camera_x;

	i = 0;
	game->player.vector = (t_fvector){cosf(game->player.angle),
		sinf(game->player.angle)};
	while (i < game->img.size.x)
	{
		camera_x = (2.f * i / (float) game->img.size.x - 1);
		ray = (t_fvector){game->player.vector.x + game->player.plane.x
			* camera_x, game->player.vector.y
			+ game->player.plane.y * camera_x};
		get_interception(game, ray, i);
		i++;
	}
}
