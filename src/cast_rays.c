/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:46:35 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:46:36 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	calculate_angle(t_fvector p, t_fvector e)
{
	const float	multiplication = p.x * e.x + p.y * e.y;
	const float	determinant = p.x * e.y - p.y * e.x;
	float		atan;

	atan = (atan2(determinant, multiplication));
	if (atan < 0)
		atan += 2 * PI;
	return (atan);
}

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
