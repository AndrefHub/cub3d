/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:39 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:47:41 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	fvector_distance(t_fvector lhs, t_fvector rhs)
{
	return (sqrtf(powf(lhs.x - rhs.x, 2) + powf(lhs.y - rhs.y, 2)));
}

int	float_sign(float f)
{
	return (1 - (f == 0.) - 2 * (f < 0.));
}
