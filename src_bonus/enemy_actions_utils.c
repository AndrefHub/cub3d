/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_actions_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:48:52 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:48:54 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	reset_panic_mode(void *en)
{
	((t_enemy *)en)->panic_mode = 0;
}

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

void	update_path(t_game *game, t_enemy *enemy, t_list **path)
{
	if (!ft_lstsize(*path))
	{
		*path = enemy->pathfinding_algorithm(game, enemy);
	}
}
