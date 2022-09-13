#include "../inc_bonus/cub3d_bonus.h"

void	update_last_collision(t_game *game)
{
	game->map->last_collision.x = game->player.pos.x;
	game->map->last_collision.y = game->player.pos.y;
}

int	radius_check(t_game *game, float x_delta, float y_delta)
{
	const t_fvector	c = (t_fvector) {game->player.pos.x + x_delta,
		game->player.pos.y + y_delta};
	// t_fvector	w;

	// w.x = ((int)c.x / MAP_GRID_SIZE) * MAP_GRID_SIZE;
	// w.y = ((int)c.y / MAP_GRID_SIZE) * MAP_GRID_SIZE;

	if (is_wall(game->map->map[((int)c.y / MAP_GRID_SIZE)][((int)c.x / MAP_GRID_SIZE) - 1])
		&& c.x - ((int)c.x / MAP_GRID_SIZE) * MAP_GRID_SIZE < PL_RADIUS)
		return (0);
	if (is_wall(game->map->map[((int)c.y / MAP_GRID_SIZE)][((int)c.x / MAP_GRID_SIZE) + 1])
		&& ((int)c.x / MAP_GRID_SIZE + 1) * MAP_GRID_SIZE - c.x < PL_RADIUS)
		return (0);
	if (is_wall(game->map->map[((int)c.y / MAP_GRID_SIZE) - 1][((int)c.x / MAP_GRID_SIZE)])
		&& c.y - ((int)c.y / MAP_GRID_SIZE) * MAP_GRID_SIZE < PL_RADIUS)
		return (0);
	if (is_wall(game->map->map[((int)c.y / MAP_GRID_SIZE) + 1][((int)c.x / MAP_GRID_SIZE)])
		&& ((int)c.y / MAP_GRID_SIZE + 1) * MAP_GRID_SIZE - c.y < PL_RADIUS)
		return (0);
	// if (is_wall(game->map->map[(int)w.y / MAP_GRID_SIZE][(int)w.x / MAP_GRID_SIZE]) && fvector_distance(c, w) < PL_RADIUS)
	// 	return (0);
	// w.x += MAP_GRID_SIZE;
	// if (is_wall(game->map->map[(int)w.y / MAP_GRID_SIZE][(int)w.x / MAP_GRID_SIZE]) && fvector_distance(c, w) < PL_RADIUS)
	// 	return (0);
	// w.y += MAP_GRID_SIZE;
	// if (is_wall(game->map->map[(int)w.y / MAP_GRID_SIZE][(int)w.x / MAP_GRID_SIZE]) && fvector_distance(c, w) < PL_RADIUS)
	// 	return (0);
	// w.x -= MAP_GRID_SIZE;
	// if (is_wall(game->map->map[(int)w.y / MAP_GRID_SIZE][(int)w.x / MAP_GRID_SIZE]) && fvector_distance(c, w) < PL_RADIUS)
	// 	return (0);
	return (1);
}

void	move_radius_check(t_game *game, float x_delta, float y_delta, int *collision)
{
	// if (radius_check(game, x_delta, 0))
		game->player.pos.x += x_delta;
	// else
	// {
	// 	if (game->map->last_collision.x != game->player.pos.x && game->map->last_collision.y != game->player.pos.y)
	// 		++(*collision);
	// 	update_last_collision(game);
	// }
	// if (radius_check(game, 0, y_delta))
		game->player.pos.y += y_delta;
	// else
	// {
	// 	if (game->map->last_collision.x != game->player.pos.x && game->map->last_collision.y != game->player.pos.y)
	// 		++(*collision);
	// 	update_last_collision(game);
	// }
	(void)collision;
}

void	check_borders(t_game *game)
{
	char			tile;
	const t_vector	plus = {(int)(game->player.pos.x + PL_RADIUS),
		(int)(game->player.pos.y + PL_RADIUS)};
	const t_vector	minus = {(int)(game->player.pos.x - PL_RADIUS),
		(int)(game->player.pos.y - PL_RADIUS)};

	tile = game->grid[(int)game->player.pos.y][minus.x];
	if (is_wall(tile))
		game->player.pos.x = (minus.x + 1) + PL_RADIUS;
	tile = game->grid[(int)game->player.pos.y][plus.x];
	if (is_wall(tile))
		game->player.pos.x = plus.x - PL_RADIUS;
	tile = game->grid[minus.y][(int)game->player.pos.x];
	if (is_wall(tile))
		game->player.pos.y = (minus.y + 1) + PL_RADIUS;
	tile = game->grid[plus.y][(int)game->player.pos.x];
	if (is_wall(tile))
		game->player.pos.y = plus.y - PL_RADIUS;

}

void	check_restrictions(t_game *game)
{
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	if (game->player.pos.x > game->map->map_size.x)
		game->player.pos.x -= 1;
	if (game->player.pos.x < 0)
		game->player.pos.x += 1;
	if (game->player.pos.y > game->map->map_size.y)
		game->player.pos.y -= 1;
	if (game->player.pos.y < 0)
		game->player.pos.y += 1;
	if (game->horizon > game->img.size.y)
		game->horizon = game->img.size.y;
	if (game->horizon < -game->img.size.y)
		game->horizon = -game->img.size.y;
	check_borders(game);
}
