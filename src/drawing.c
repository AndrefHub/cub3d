#include "../inc/cub3d.h"

void	draw_line(t_img *img, t_vector p1, t_vector p2, int color)
{
	const t_vector	diff = {abs(p2.x - p1.x), -abs(p2.y - p1.y)};
	const int		step_x = (p1.x < p2.x) - (p1.x >= p2.x);
	const int		step_y = (p1.y < p2.y) - (p1.y >= p2.y);
	int				error;
	int				error_2;

	error = diff.x + diff.y;
	while (1)
	{
		img->addr[p1.y * img->size.x + p1.x] = color;
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		error_2 = 2 * error;
		if (error_2 >= diff.y)
		{
			error += diff.y;
			p1.x += step_x;
		}
		if (error_2 <= diff.x)
		{
			error += diff.x;
			p1.y += step_y;
		}
	}
}

void	draw_square_fill(t_img *img, t_vector top_left, int size, int color)
{
	t_vector	px;

	px.y = top_left.y;
	while (px.y < top_left.y + size)
	{
		px.x = top_left.x;
		while (px.x < top_left.x + size)
		{
			img->addr[px.y * img->size.x + px.x] = color;
			px.x++;
		}
		px.y++;
	}
}

// void	draw_rectangle_fill(t_img *img, t_vector top_left, t_vector size, int color)
// {
// 	t_vector	px;

// 	px.y = top_left.y;
// 	while (px.y < top_left.y + size.y)
// 	{
// 		px.x = top_left.x;
// 		while (px.x < top_left.x + size.x)
// 		{
// 			put_pixel_on_pixel((t_rgb *)img->addr + px.y * img->size.x + px.x,
// 				(t_rgb *)(&color));
// 			px.x++;
// 		}
// 		px.y++;
// 	}
// }

void	draw_aim(t_game *game)
{
	draw_square_fill(&game->img, (t_vector){game->img.size.x / 2 - AIM_SIZE / 2,
		game->img.size.y / 2 - AIM_SIZE / 2}, AIM_SIZE, AIM_COLOR);
}
