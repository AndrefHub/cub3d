#include "../inc_bonus/cub3d_bonus.h"

t_ray	ray_initialize(t_game *game, t_fvector ray_dir)
{
	t_ray ray;

	ray.dir = ray_dir;
	ray.unit = (t_fvector) {sqrtf(1 + (ray.dir.y / ray.dir.x) * (ray.dir.y / ray.dir.x)),
							sqrtf(1 + (ray.dir.x / ray.dir.y) * (ray.dir.x / ray.dir.y))};
	ray.map_tile = (t_vector) {game->player.pos.x, game->player.pos.y};
	if (ray.dir.x < 0)
	{
		ray.step.x = -1;
		ray.length.x =
				(game->player.pos.x - (float) ray.map_tile.x) * ray.unit.x;
	}
	else
	{
		ray.step.x = 1;
		ray.length.x = (((float) ray.map_tile.x + 1) - game->player.pos.x) *
					   ray.unit.x;
	}
	if (ray.dir.y < 0)
	{
		ray.step.y = -1;
		ray.length.y =
				(game->player.pos.y - (float) ray.map_tile.y) * ray.unit.y;
	}
	else
	{
		ray.step.y = 1;
		ray.length.y = (((float) ray.map_tile.y + 1) - game->player.pos.y)
			* ray.unit.y;
	}
	return (ray);
}

float	interception_distance(t_game *game, t_ray *ray)
{
	float	distance;

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
			ray->map_tile.y < game->map->map_size.y &&
			ray->map_tile.x < game->map->map_size.x)
		{
			if (is_wall(game->grid[ray->map_tile.y]
						[ray->map_tile.x]))
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
		camera = game->player.angle - ray_angle;
		if (camera < 0)
			camera += 2 * PI;
		if (camera > 2 * PI)
			camera -= 2 * PI;
		game->column[i].height = game->col_scale / distance;
		game->column[i].perp_dist = distance * cosf(camera);
		game->column[i].pos = (t_fvector) {game->player.pos.x + cosf(ray_angle)
																* distance, game->player.pos.y + sinf(ray_angle) * distance};
		if (ray->length.y - ray->unit.y < ray->length.x - ray->unit.x)
		{
			game->column[i].fade = 2.f;
			game->column[i].dir = "SN"[(int) (game->column[i].pos.x > game->player.pos.x)];
			game->column[i].texture_pos = game->column[i].pos.y;
		}
		else
		{
			game->column[i].fade = 1.f;
			game->column[i].dir = "EW"[(int) (game->column[i].pos.y > game->player.pos.y)];
			game->column[i].texture_pos = game->column[i].pos.x;
		}
		if (game->column[i].dir == 'W' || game->column[i].dir == 'S')
			game->column[i].texture_pos = TEXTURE_SIZE - game->column[i].texture_pos;
		game->column[i].texture_pos = game->column[i].texture_pos * TEXTURE_SIZE;
		if (distance > MAX_RENDER_DISTANCE)
			game->column[i].color = 0xFFAAAA;
		game->column[i].distance = distance;
		game->column[i].ray_dir = ray->dir;
		game->column[i].cell = (t_vector) {ray->map_tile.x, ray->map_tile.y};
	}
	else
	{
		game->column->height = 1;
		game->column[i].color = 0x00DCE7;
		game->column->distance = 1000;
	}
}

void	get_interception(t_game *game, t_fvector ray_dir, int i)
{
	t_ray	ray;
	float	distance;

	ray = ray_initialize(game, ray_dir);
	distance = interception_distance(game, &ray);
	initialize_columns(game, &ray, distance, i,
		calculate_angle((t_fvector){1, 0}, ray_dir));
}

void	cast_rays(t_game *game)
{
	int			i;
	t_fvector	ray;
	float		camera_x;

	i = 0;
	game->player.vector = (t_fvector) {cosf(game->player.angle),
		sinf(game->player.angle)};
	while (i < game->img.size.x)
	{
		camera_x = (2.f * i / (float) game->img.size.x - 1);
		ray = (t_fvector){game->player.vector.x + game->player.plane.x
			* camera_x, game->player.vector.y
			+ game->player.plane.y * camera_x};
		get_interception(game, ray, i);
		i++;
	}
}
