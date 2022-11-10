/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:01 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:42:01 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	in_bounds_vec(t_vector map_size, t_vector obj)
{
	return (0 < obj.x && obj.x < map_size.x - 1 && 0 < obj.y
		&& obj.y < map_size.y - 1);
}

int	in_bounds(t_vector map_size, int x, int y)
{
	return (0 < x && x < map_size.x - 1 && 0 < y && y < map_size.y - 1);
}
