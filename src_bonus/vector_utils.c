/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:59 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:51:06 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

float	fvector_distance(t_fvector lhs, t_fvector rhs)
{
	return (sqrtf(powf(lhs.x - rhs.x, 2) + powf(lhs.y - rhs.y, 2)));
}

int	float_sign(float f)
{
	return (1 - (f == 0.) - 2 * (f < 0.));
}
