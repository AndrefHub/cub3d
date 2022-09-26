#include "../inc_bonus/cub3d_bonus.h"

void	put_pixel(t_img *img, t_vector point, int color)
{
	if (point.x >= img->size.x || point.y >= img->size.y
		|| point.x < 0 || point.y < 0)
		return ;
	img->addr[point.y * img->size.x + point.x] = color;
}

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
		put_pixel(img, p1, color);
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
			put_pixel(img, px, color);
			px.x++;
		}
		px.y++;
	}
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
	int	img_size = img->size.x * (img->size.y / 2 - horizon);
	int			i;

	if (horizon > img->size.y / 2)
		return ;
	if (img_size > img->size.x * img->size.y)
		img_size = img->size.x * img->size.y;
	i = 0;
	while (i < img_size)
		img->addr[i++] = color;
}

void	draw_player(t_game *game)
{
	(void) game;
}

void	draw_aim(t_game *game)
{
	draw_square_fill(&game->img, (t_vector){game->img.size.x / 2 - AIM_SIZE / 2,
	game->img.size.y / 2 - AIM_SIZE / 2}, AIM_SIZE, AIM_COLOR);
}
