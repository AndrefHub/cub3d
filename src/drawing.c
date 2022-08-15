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

float	get_interception(t_game *game, float ray_angle, int i) //DDA algorithm
{
	t_fvector	ray_unit;
	t_fvector	ray_dir;
	t_vector	map_tile;
	t_fvector	ray_length;
	t_vector	step;
	t_fvector	ray_start;

	ray_start = game->player.pos;
	ray_dir.x = cosf(ray_angle);
	ray_dir.y = sinf(ray_angle);
	ray_unit = (t_fvector) {sqrtf(1 + tanf(ray_angle) * tanf(ray_angle)), sqrtf(1 +
							1 / (tanf(ray_angle) * tanf(ray_angle)))};
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

	bool	tile_found;
	float	distance;
	float	max_distance;

	tile_found = 0;
	distance = 0.0f;
	max_distance = MAX_RENDER_DISTANCE;
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

		//TODO: add outOfBounds check
//		if (map_tile.y / MAP_GRID_SIZE <= ft_arraylen((void **) game->grid) && map_tile.x / MAP_GRID_SIZE <=
//																					   (int) ft_strlen(game->grid[map_tile.y / MAP_GRID_SIZE]))
//		{
			if (game->grid[map_tile.y / MAP_GRID_SIZE][map_tile.x /
													   MAP_GRID_SIZE] == '1') {
				if (ray_length.x - ray_unit.x > ray_length.y - ray_unit.y)
					game->column[i].color = 0x009CA4;
				else
					game->column[i].color = 0x00DCE7;
				tile_found = true;
				break ;
			}
//		}
	}

	float camera;

	if (tile_found)
	{
//		*res = (t_fvector) {ray_start.x + ray_dir.x * distance, ray_start.y + ray_dir.y * distance};
//		if (ray_length.x > ray_length.y)
//			game->column[i].color = 0x009CA4;
//		else
//			game->column[i].color = 0x00DCE7;
	}
	else
	{
//		*res = (t_fvector) {0.0f, 0.0f};
//		game->column->color = 0x00DCE7;
		game->column->distance = 0;
	}
	camera = game->player.angle - ray_angle;
	if (camera < 0)
		camera += 2 * PI;
	if (camera > 2 * PI)
		camera -= 2 * PI;
	game->column[i].height = (MAP_GRID_SIZE * ABS_WALL_SIZE) / (distance * cosf(camera));
	if (game->column[i].height > game->img.size.y)
		game->column[i].height = game->img.size.y;
	game->column[i].pos = (t_fvector) {game->player.pos.x + cos(ray_angle) * distance, game->player.pos.y + sin(ray_angle) * distance};
	game->column[i].distance = distance;
	return (0);
}

void	draw_3D(t_game *game)
{
	int		i;
	int		k;

	i = 0;
	while (i < game->img.size.x)
	{
		k = game->img.size.y / 2 - game->column[i].height / 2;
		while (k < game->img.size.y / 2 + game->column[i].height / 2)
		{
//			put_pixel(&game->img, (t_vector) {i, k}, game->column[i].color);
			game->img.addr[k * game->img.size.x + i] = game->column[i].color;
			k++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	(void) game;
}

void	draw_aim(t_game *game)
{
	draw_square_fill(&game->img, (t_vector ) {game->img.size.x / 2 - AIM_SIZE / 2, game->img.size.y / 2 - AIM_SIZE / 2}, AIM_SIZE, AIM_COLOR);
}
