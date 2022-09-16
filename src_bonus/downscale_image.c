#include "../inc_bonus/cub3d_bonus.h"

int	get_downscaled_color(t_img *img, int divisor, t_vector pos)
{
	t_rgb		color;
	int			channels[4];
	t_vector	vec;

	ft_bzero(channels, sizeof(*channels) * 4);
	vec.y = pos.y;
	while (vec.y - pos.y < divisor)
	{
		vec.x = pos.x;
		while (vec.x - pos.x < divisor)
		{
			color = *(t_rgb *)(img->addr + vec.y * img->size.x + vec.x);
			channels[0] += color.a;
			channels[1] += color.r;
			channels[2] += color.g;
			channels[3] += color.b;
			++vec.x;
		}
		++vec.y;
	}
	color.a = channels[0] / (divisor * divisor);
	color.r = channels[1] / (divisor * divisor);
	color.g = channels[2] / (divisor * divisor);
	color.b = channels[3] / (divisor * divisor);
	return (*(int *)(&color));
}

void	put_downscaled_image(t_img *dst, t_vector pos, t_img *src, int divisor)
{
	int	xcounter;
	int	ycounter;

	ycounter = -1;
	while (++ycounter < src->size.y / divisor)
	{
		xcounter = -1;
		while (++xcounter < src->size.x / divisor)
		{
			put_pixel(dst, (t_vector){pos.x + xcounter, pos.y + ycounter},
				get_downscaled_color(src, divisor,
					(t_vector){xcounter * divisor, ycounter * divisor}));
		}
	}
}
