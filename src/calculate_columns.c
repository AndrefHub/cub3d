#include "../inc/cub3d.h"

t_ray	ray_initialize(t_game *game, t_fvector ray_dir)
{
	t_ray	ray;

	ray.dir = ray_dir;
	ray.unit.x = sqrtf(1 + (ray.dir.y / ray.dir.x) * (ray.dir.y / ray.dir.x));
	ray.unit.y = sqrtf(1 + (ray.dir.x / ray.dir.y) * (ray.dir.x / ray.dir.y));
	ray.map_tile = (t_vector){game->player.pos.x, game->player.pos.y};
	ray.step.x = -1 + 2 * (ray_dir.x > 0);
	if (ray.dir.x < 0)
		ray.len.x = (game->player.pos.x - ray.map_tile.x) * ray.unit.x;
	else
		ray.len.x = ((ray.map_tile.x + 1.f) - game->player.pos.x) * ray.unit.x;
	if (ray.dir.y < 0)
	{
		ray.step.y = -1;
		ray.len.y = (game->player.pos.y - ray.map_tile.y) * ray.unit.y;
	}
	else
	{
		ray.step.y = 1;
		ray.len.y = ((ray.map_tile.y + 1.f) - game->player.pos.y) * ray.unit.y;
	}
	return (ray);
}

float	interception_distance(t_game *game, t_ray *ray)
{
	float	distance;

	distance = 0.0f;
	while (distance < MAX_RENDER_DISTANCE)
	{
		if (ray->len.x < ray->len.y)
		{
			ray->map_tile.x += ray->step.x;
			distance = ray->len.x;
			ray->len.x += ray->unit.x;
		}
		else
		{
			ray->map_tile.y += ray->step.y;
			distance = ray->len.y;
			ray->len.y += ray->unit.y;
		}
		if (ray->map_tile.y >= 0 && ray->map_tile.x >= 0
			&& ray->map_tile.y < game->map->map_size.y
			&& ray->map_tile.x < game->map->map_size.x)
			if (is_wall(game->grid[ray->map_tile.y][ray->map_tile.x]))
				break ;
	}
	return (distance);
}

void	calculate_column_dir(t_game *g, t_ray *ray, int i)
{
	if (ray->len.y - ray->unit.y < ray->len.x - ray->unit.x)
	{
		g->col[i].dir = "SN"[(int)(g->col[i].pos.x > g->player.pos.x)];
		g->col[i].texture_pos = g->col[i].pos.y;
	}
	else
	{
		g->col[i].dir = "EW"[(int)(g->col[i].pos.y > g->player.pos.y)];
		g->col[i].texture_pos = g->col[i].pos.x;
	}
}

void	initialize_columns(t_game *g, t_ray *ray, int i, float r_angle)
{
	float	camera;

	if (g->col[i].dist < MAX_RENDER_DISTANCE)
	{
		camera = g->player.angle - r_angle;
		if (camera < 0)
			camera += 2 * PI;
		if (camera > 2 * PI)
			camera -= 2 * PI;
		g->col[i].height = g->col_scale / g->col[i].dist;
		g->col[i].perp_dist = g->col[i].dist * cosf(camera);
		g->col[i].pos = (t_fvector){g->player.pos.x + cosf(r_angle)
			* g->col[i].dist, g->player.pos.y + sinf(r_angle) * g->col[i].dist};
		calculate_column_dir(g, ray, i);
		g->col[i].texture_pos = g->col[i].texture_pos * TEXTURE_SIZE;
		g->col[i].dist = g->col[i].dist;
		g->col[i].ray_dir = ray->dir;
		g->col[i].cell = (t_vector){ray->map_tile.x, ray->map_tile.y};
	}
	else
	{
		g->col->height = 1;
		g->col[i].color = 0x00DCE7;
		g->col->dist = 1000;
	}
}
