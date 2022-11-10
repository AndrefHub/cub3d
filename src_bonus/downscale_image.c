/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   downscale_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:57 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:26:14 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	get_downscaled_colored_font(t_img *img,
	int divisor, t_vector pos, t_rgb color)
{
	t_rgb		pixel;
	int			alpha;
	t_vector	vec;

	alpha = 0;
	*(int *)(&pixel) = 0;
	vec.y = pos.y;
	while (vec.y - pos.y < divisor)
	{
		vec.x = pos.x;
		while (vec.x - pos.x < divisor)
		{
			pixel = *(t_rgb *)(img->addr + vec.y * img->size.x + vec.x);
			alpha += pixel.a;
			++vec.x;
		}
		++vec.y;
	}
	pixel.a = alpha / (divisor * divisor);
	pixel.a = 0xFF * (pixel.a >= 0x7F);
	pixel.r = color.r;
	pixel.g = color.g;
	pixel.b = color.b;
	return (*(int *)(&pixel));
}

void	put_downscaled_image(t_img *dst, t_text *text, t_img *src, int divisor)
{
	int		xcounter;
	int		ycounter;
	int		texture_pix;
	t_rgb	*color;

	color = ((t_rgb *)(&text->color));
	ycounter = -1;
	while (++ycounter < src->size.y / divisor)
	{
		xcounter = -1;
		while (++xcounter < src->size.x / divisor)
		{
			texture_pix = get_downscaled_colored_font(src, divisor,
					(t_vector){xcounter * divisor, ycounter * divisor}, *color);
			if (texture_pix > 0x000000)
				put_pixel_on_pixel((t_rgb *)dst->addr + (text->pos.y + ycounter)
					* dst->size.x + (text->pos.x + xcounter),
					(t_rgb *)&texture_pix);
		}
	}
}
