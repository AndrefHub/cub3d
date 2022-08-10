#include "../inc/cub3d.h"

void	put_pixel(t_img *img, t_vector point, int color)
{
	if (point.x >= img->size.x || point.y >= img->size.y || point.x < 0 || point.y < 0)
		return ;
	img->addr[point.y * img->size.x + point.x] = color;
}

//Bresenham's line algorithm
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

void	img_clear_rgb(t_img *img, int color)
{
	const int	img_size = img->size.x * img->size.y;
	int			i;

	i = 0;
	while (i < img_size)
		img->addr[i++] = color;
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->grid[y])
	{
		x = 0;
		while (game->grid[y][x])
		{
			if (game->grid[y][x] == '0' || game->grid[y][x] == 'N')
				draw_square_fill(&game->img,
								 (t_vector) {x * game->size, y * game->size},
								 game->size, 0xFFFFFF);
			else if (game->grid[y][x] == '1')
				draw_square_fill(&game->img,
								 (t_vector) {x * game->size, y * game->size},
								 game->size, 0x000000);
			x++;
		}
		y++;
	}
}

t_fvector	get_interception(t_game *game, double ray_angle) //DDA algorithm
{
	t_fvector	ray_unit;
	t_fvector	ray_dir;
	t_vector	map_tile;
	t_fvector	ray_length;
	t_vector	step;
	t_fvector	ray_start;

	ray_start = game->player.pos;
	ray_dir.x = cos(ray_angle);
	ray_dir.y = sin(ray_angle);
	ray_unit = (t_fvector) {sqrt(1 + (ray_dir.y / ray_dir.x) * (ray_dir.y / ray_dir.x)), sqrt(1 + (ray_dir.x / ray_dir.y) * (ray_dir.x / ray_dir.y))};
	map_tile = (t_vector) {game->player.pos.x, game->player.pos.y};

	if (ray_dir.x < 0)
	{
		step.x = -1;
		ray_length.x = (ray_start.x - (float ) map_tile.x) * ray_unit.x;
	}
	else
	{
		step.x = 1;
		ray_length.x = (((float ) map_tile.x + 1) - ray_start.x) * ray_unit.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		ray_length.y = (ray_start.y - (float ) map_tile.y) * ray_unit.y;
	}
	else
	{
		step.y = 1;
		ray_length.y = (((float ) map_tile.y + 1) - ray_start.y) * ray_unit.y;
	}

	int		tile_found;
	float	distance;
	float	max_distance;

	tile_found = 0;
	distance = 0.0f;
	max_distance = 1080.0f;
	while (!tile_found && distance < max_distance)
	{
		if (ray_length.x < ray_length.y)
		{
			map_tile.x += step.x;
			distance = ray_length.x;
			ray_length.x += ray_unit.x;
		}
		else
		{
			map_tile.y += step.y;
			distance = ray_length.y;
			ray_length.y += ray_unit.y;
		}

		if (game->grid[map_tile.y / MAP_GRID_SIZE][map_tile.x / MAP_GRID_SIZE] == '1')
		{
			tile_found = 1;
		}
	}

	if (tile_found)
		return ((t_fvector) {ray_start.x + ray_dir.x * distance, ray_start.y + ray_dir.y * distance});
	else
		return ((t_fvector) {0.0f, 0.0f});
}

void	draw_rays(t_game *game)
{
		double	ray_angle;
		int i;
		t_fvector ray;

		i = 0;
		while (i < 60)
		{
			ray_angle = game->player.angle - 0.1667f * PI + 0.01f * i;
			ray = get_interception(game, ray_angle);
			draw_line(&game->img, (t_vector) {game->player.pos.x, game->player.pos.y} , (t_vector) {ray.x, ray.y}, 0x0000FF);
			i++;
		}
}

void	draw_player(t_game *game)
{
	draw_square_fill(&game->img, (t_vector) {game->player.pos.x, game->player.pos.y}, MAP_GRID_SIZE / 2, 0xFF0000);
	draw_rays(game);
	draw_line(&game->img, (t_vector) {game->player.pos.x + MAP_GRID_SIZE / 4, game->player.pos.y + MAP_GRID_SIZE / 4},
			  (t_vector) {game->player.pos.x + game->player.delta.x * 5 + MAP_GRID_SIZE / 4, game->player.pos.y + game->player.delta.y * 5 + MAP_GRID_SIZE / 4}, 0xFF0000);
}
