#include "../inc_bonus/cub3d_bonus.h"

int	get_downscaled_color(t_img *img, int divisor, t_vector pos)
{
	t_rgb		color;
	int			channels[4];
	t_vector	vec;

	ft_bzero(channels, sizeof(*channels) * 4);
	*(int *)(&color) = 0;
	vec.y = pos.y;
	while (vec.y - pos.y < divisor)
	{
		vec.x = pos.x;
		while (vec.x - pos.x < divisor)
		{
			color = *(t_rgb *)(img->addr + vec.y * img->size.x + vec.x);
			channels[0] += color.a;
			channels[1] += color.r * color.a;
			channels[2] += color.g * color.a;
			channels[3] += color.b * color.a;
			++vec.x;
		}
		++vec.y;
	}
	if (channels[0])
	{	
		// color.a = (((channels[0]) / (divisor * divisor)) >> 7) << 7;
		color.a = 0x7F * (channels[0] != 0) + 0x80 * (channels[0] > 0x7F * (divisor * divisor)); //
		color.r = channels[1] / (divisor * divisor * channels[0]);
		color.g = channels[2] / (divisor * divisor * channels[0]);
		color.b = channels[3] / (divisor * divisor * channels[0]);
	}
	return (*(int *)(&color));
}

int	get_downscaled_colored_font(t_img *img, int divisor, t_vector pos, t_rgb color)
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
	// pixel.a = 0x7F * (pixel.a > 0x3F) + 0x80 * (pixel.a > 0xBF);
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
				put_pixel_on_pixel((t_rgb *)dst->addr + (text->pos.y + ycounter) * dst->size.x + (text->pos.x + xcounter), (t_rgb *)&texture_pix); //dst->addr[(text->pos.y + ycounter) * dst->size.x + (text->pos.x + xcounter)] = texture_pix;
		}
	}
}
