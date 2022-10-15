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

void	check_borders_enemy(t_game *game, t_object *object)
{
	char			tile;
	const t_vector	plus = {(int)(object->pos.x + PL_RADIUS),
		(int)(object->pos.y + PL_RADIUS)};
	const t_vector	minus = {(int)(object->pos.x - PL_RADIUS),
		(int)(object->pos.y - PL_RADIUS)};

	tile = game->grid[(int)object->pos.y][minus.x];
	if (is_wall(tile))
		object->pos.x = (minus.x + 1) + PL_RADIUS;
	tile = game->grid[(int)object->pos.y][plus.x];
	if (is_wall(tile))
		object->pos.x = plus.x - PL_RADIUS;
	tile = game->grid[minus.y][(int)object->pos.x];
	if (is_wall(tile))
		object->pos.y = (minus.y + 1) + PL_RADIUS;
	tile = game->grid[plus.y][(int)object->pos.x];
	if (is_wall(tile))
		object->pos.y = plus.y - PL_RADIUS;
}

void	check_borders(t_game *game, struct s_player *object)
{
	char			tile;
	const t_vector	plus = {(int)(object->pos.x + PL_RADIUS),
		(int)(object->pos.y + PL_RADIUS)};
	const t_vector	minus = {(int)(object->pos.x - PL_RADIUS),
		(int)(object->pos.y - PL_RADIUS)};

	tile = game->grid[(int)object->pos.y][minus.x];
	if (is_wall(tile))
		object->pos.x = (minus.x + 1) + PL_RADIUS;
	tile = game->grid[(int)object->pos.y][plus.x];
	if (is_wall(tile))
		object->pos.x = plus.x - PL_RADIUS;
	tile = game->grid[minus.y][(int)object->pos.x];
	if (is_wall(tile))
		object->pos.y = (minus.y + 1) + PL_RADIUS;
	tile = game->grid[plus.y][(int)object->pos.x];
	if (is_wall(tile))
		object->pos.y = plus.y - PL_RADIUS;
}

// void	check_borders_enemy(t_game *game, t_enemy *player)
// {
// 	char			tile;
// 	const t_vector	plus = {(int)(player->object.pos.x + PL_RADIUS),
// 		(int)(player->object.pos.y + PL_RADIUS)};
// 	const t_vector	minus = {(int)(player->object.pos.x - PL_RADIUS),
// 		(int)(player->object.pos.y - PL_RADIUS)};

// 	tile = game->grid[(int)player->object.pos.y][minus.x];
// 	if (is_wall(tile))
// 		player->object.pos.x = (minus.x + 1) + PL_RADIUS;
// 	tile = game->grid[(int)player->object.pos.y][plus.x];
// 	if (is_wall(tile))
// 		player->object.pos.x = plus.x - PL_RADIUS;
// 	tile = game->grid[minus.y][(int)player->object.pos.x];
// 	if (is_wall(tile))
// 		player->object.pos.y = (minus.y + 1) + PL_RADIUS;
// 	tile = game->grid[plus.y][(int)player->object.pos.x];
// 	if (is_wall(tile))
// 		player->object.pos.y = plus.y - PL_RADIUS;
// }

void	check_restrictions(t_game *game)
{
	if (game->player.angle <= 0)
		game->player.angle += 2 * PI;
	if (game->player.angle >= 2 * PI)
		game->player.angle -= 2 * PI;
	if (game->z_offset > game->img.size.y)
		game->z_offset = game->img.size.y;
	if (game->z_offset < -game->img.size.y)
		game->z_offset = -game->img.size.y;
	check_borders(game, &game->player);
}
