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
	const t_vector	plus = {(int)(player->pos.x + PL_RADIUS),
		(int)(player->pos.y + PL_RADIUS)};
	const t_vector	minus = {(int)(player->pos.x - PL_RADIUS),
		(int)(player->pos.y - PL_RADIUS)};

	tile = game->grid[(int)player->pos.y][minus.x];
	if (is_wall(tile))
		player->pos.x = (minus.x + 1) + PL_RADIUS;
	tile = game->grid[(int)player->pos.y][plus.x];
	if (is_wall(tile))
		player->pos.x = plus.x - PL_RADIUS;
	tile = game->grid[minus.y][(int)player->pos.x];
	if (is_wall(tile))
		player->pos.y = (minus.y + 1) + PL_RADIUS;
	tile = game->grid[plus.y][(int)player->pos.x];
	if (is_wall(tile))
		player->pos.y = plus.y - PL_RADIUS;

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
	check_borders(game, (t_enemy *)&game->player);
}
