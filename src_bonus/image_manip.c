/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:46 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:49:47 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	dim_image(t_img *img, int img_size, t_rgb *color)
{
	int				counter;
	t_rgb			*rgb;

	counter = -1;
	if (color->a == 0xFF)
		while (++counter < img_size)
			img->addr[counter] = *(int *)color;
	while (++counter < img_size)
	{
		rgb = (t_rgb *)(img->addr + counter);
		rgb->r += ((color->r - rgb->r) * color->a) / (1 << 8);
		rgb->g += ((color->g - rgb->g) * color->a) / (1 << 8);
		rgb->b += ((color->b - rgb->b) * color->a) / (1 << 8);
	}
}

void	dim_screen(t_game *game, int i)
{		
	dim_image(&game->img, game->img.size.x * game->img.size.y,
		&(t_rgb){0, 0, 0, 0xFF / (50 - i)});
	mlx_put_image_to_window(game->mlx.id, game->mlx.window,
		game->img.mlx_img, (game->mlx.win_size.x - game->img.size.x) / 2, 0);
}
