/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:48:37 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:48:39 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	put_pixel(t_img *img, t_vector point, int color)
{
	if (point.x >= img->size.x || point.y >= img->size.y
		|| point.x < 0 || point.y < 0)
		return ;
	img->addr[point.y * img->size.x + point.x] = color;
}

void	fill_img_color(t_img *img, int color)
{
	const int	img_size = img->size.x * img->size.y;
	int			i;

	i = 0;
	while (i < img_size)
		img->addr[i++] = color;
}

void	fill_floor_color(t_img *img, int color, int horizon)
{
	int	i;

	if (-horizon > img->size.y / 2)
		return ;
	i = img->size.x * (img->size.y / 2 - horizon);
	if (i < 0)
		i = 0;
	while (i < img->size.x * img->size.y)
		img->addr[i++] = color;
}

void	fill_ceiling_color(t_img *img, int color, int horizon)
{
	int	img_size;
	int	i;

	img_size = img->size.x * (img->size.y / 2 - horizon);
	if (horizon > img->size.y / 2)
		return ;
	if (img_size > img->size.x * img->size.y)
		img_size = img->size.x * img->size.y;
	i = 0;
	while (i < img_size)
		img->addr[i++] = color;
}
