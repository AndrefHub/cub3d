#include "../inc_bonus/cub3d_bonus.h"

void	update_last_collision(t_game *game)
{
	game->map->last_collision.x = game->player.pos.x;
	game->map->last_collision.y = game->player.pos.y;
}

void	move_radius_check(t_game *game, float x_delta, float y_delta, int *collision)
{
	game->player.pos.x += x_delta;
	game->player.pos.y += y_delta;
	(void)collision;
}

void	check_borders(t_game *game, t_enemy *player)
{
	char			tile;
	const t_vector	plus = {(int)(player->pos.x + PL_RADIUS) / MAP_GRID_SIZE,
		(int)(player->pos.y + PL_RADIUS) / MAP_GRID_SIZE};
	const t_vector	minus = {(int)(player->pos.x - PL_RADIUS) / MAP_GRID_SIZE,
		(int)(player->pos.y - PL_RADIUS) / MAP_GRID_SIZE};

	tile = game->grid[(int)player->pos.y / MAP_GRID_SIZE][minus.x];
	if (is_wall(tile))
		player->pos.x = (minus.x + 1) * MAP_GRID_SIZE + PL_RADIUS;
	tile = game->grid[(int)player->pos.y / MAP_GRID_SIZE][plus.x];
	if (is_wall(tile))
		player->pos.x = plus.x * MAP_GRID_SIZE - PL_RADIUS;
	tile = game->grid[minus.y][(int)player->pos.x / MAP_GRID_SIZE];
	if (is_wall(tile))
		player->pos.y = (minus.y + 1) * MAP_GRID_SIZE + PL_RADIUS;
	tile = game->grid[plus.y][(int)player->pos.x / MAP_GRID_SIZE];
	if (is_wall(tile))
		player->pos.y = plus.y * MAP_GRID_SIZE - PL_RADIUS;
}

void	check_restrictions(t_game *game)
{
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	if (game->player.pos.x > game->map->map_size.x * MAP_GRID_SIZE)
		game->player.pos.x -= MAP_GRID_SIZE;
	if (game->player.pos.x < 0)
		game->player.pos.x += MAP_GRID_SIZE;
	if (game->player.pos.y > game->map->map_size.y * MAP_GRID_SIZE)
		game->player.pos.y -= MAP_GRID_SIZE;
	if (game->player.pos.y < 0)
		game->player.pos.y += MAP_GRID_SIZE;
	if (game->player.angle_y > 500)
		game->player.angle_y = 500;
	if (game->player.angle_y < -500)
		game->player.angle_y = -500;
	check_borders(game, (t_enemy *)&game->player);
}
