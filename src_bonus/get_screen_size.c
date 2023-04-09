/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_screen_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:42 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:49:44 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void normalize_resolution(int *size_x, int *size_y)
{
	const int xvals[3] = {2560, 1920, 1280};
	const int yvals[3] = {1440, 1080, 720};
	int counter;

	counter = -1;
	while (++counter < 3)
	{
		if (*size_x >= xvals[counter] && *size_y >= yvals[counter])
		{
			*size_x = xvals[counter];
			*size_y = yvals[counter];
			return ;
		}
	}
}

#ifdef __APPLE__

inline void	get_screen_size(void *mlx_ptr, int *size_x, int *size_y)
{
	(void)mlx_ptr;
	mlx_get_screen_size(size_x, size_y);
	normalize_resolution(size_x, size_y);
}

#else

inline void	get_screen_size(void *mlx_ptr, int *size_x, int *size_y)
{
	mlx_get_screen_size(mlx_ptr, size_x, size_y);
	normalize_resolution(size_x, size_y);
}

#endif
