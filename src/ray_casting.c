#include "../inc/cub3d.h"

void	draw_walls(t_game *game)
{
	int		i;
	int		k;

	i = 0;
	while (i < game->img.size.x)
	{
		k = game->img.size.y / 2 - game->column[i].height / 2;
		while (k < game->img.size.y / 2 + game->column[i].height / 2)
		{
			game->img.addr[k * game->img.size.x + i] = game->column[i].color;
			k++;
		}
		i++;
	}
}

t_ray	ray_initialize(t_game *game, float ray_angle)
{
	t_ray ray;

	ray.dir.x = cosf(ray_angle);
	ray.dir.y = sinf(ray_angle);
	ray.unit = (t_fvector) {sqrtf(1 + tanf(ray_angle) * tanf(ray_angle)),
							sqrtf(1 + 1 / (tanf(ray_angle) * tanf(ray_angle)))};
	ray.map_tile = (t_vector) {game->player.pos.x, game->player.pos.y};
	if (ray.dir.x < 0) {
		ray.step.x = -1;
		ray.length.x =
				(game->player.pos.x - (float) ray.map_tile.x) * ray.unit.x;
	} else {
		ray.step.x = 1;
		ray.length.x = (((float) ray.map_tile.x + 1) - game->player.pos.x) *
					   ray.unit.x;
	}
	if (ray.dir.y < 0) {
		ray.step.y = -1;
		ray.length.y =
				(game->player.pos.y - (float) ray.map_tile.y) * ray.unit.y;
	} else {
		ray.step.y = 1;
		ray.length.y = (((float) ray.map_tile.y + 1) - game->player.pos.y) *
					   ray.unit.y;
	}
	return (ray);
}

float	interception_distance(t_game *game, t_ray *ray)
{
	float distance;

	distance = 0.0f;
	while (distance < MAX_RENDER_DISTANCE)
	{
		if (ray->length.x < ray->length.y)
		{
			ray->map_tile.x += ray->step.x;
			distance = ray->length.x;
			ray->length.x += ray->unit.x;
		}
		else
		{
			ray->map_tile.y += ray->step.y;
			distance = ray->length.y;
			ray->length.y += ray->unit.y;
		}
		if (ray->map_tile.y >= 0 && ray->map_tile.x >= 0 &&
			ray->map_tile.y / MAP_GRID_SIZE < game->map->map_size.y &&
			ray->map_tile.x / MAP_GRID_SIZE < game->map->map_size.x) {
			if (game->grid[ray->map_tile.y / MAP_GRID_SIZE][ray->map_tile.x /
														   MAP_GRID_SIZE] ==
				'1')
				break;
		}
	}
	return (distance);
}

void	initialize_columns(t_game *game, t_ray *ray, float distance, int i, float ray_angle)
{
	float camera;

	if (distance < MAX_RENDER_DISTANCE)
	{
		if (ray->length.x - ray->unit.x > ray->length.y - ray->unit.y)
			game->column[i].color = 0x009CA4;
		else
			game->column[i].color = 0x00DCE7;
		if (distance > MAX_RENDER_DISTANCE)
			game->column[i].color = 0xFFAAAA;
		camera = game->player.angle - ray_angle;
		if (camera < 0)
			camera += 2 * PI;
		if (camera > 2 * PI)
			camera -= 2 * PI;
		game->column[i].height = (MAP_GRID_SIZE * ABS_WALL_SIZE) / (distance
			* cosf(camera));
		if (game->column[i].height > game->img.size.y)
			game->column[i].height = game->img.size.y;
		game->column[i].pos = (t_fvector) {game->player.pos.x + cos(ray_angle)
			* distance, game->player.pos.y + sin(ray_angle) * distance};
		game->column[i].distance = distance;
	}
	else
	{
		game->column->height = 1;
		game->column[i].color = 0x00DCE7;
		game->column->distance = 1000;
	}
}

void	get_interception(t_game *game, float ray_angle, int i) //DDA algorithm
{
	t_ray	ray;
	float	distance;

	ray = ray_initialize(game, ray_angle);
	distance = interception_distance(game, &ray);
	initialize_columns(game, &ray, distance, i, ray_angle);
}