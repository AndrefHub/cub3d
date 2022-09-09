#include "../inc_bonus/cub3d_bonus.h"

void	update_last_collision(t_game *game)
{
	game->map->last_collision.x = game->player.pos.x;
	game->map->last_collision.y = game->player.pos.y;
}

void	move_radius_check(t_game *game, float x_delta, float y_delta, int *collision)
{
	if (!is_wall(game->map->map[(int)game->player.pos.y / MAP_GRID_SIZE]
				 [(int)(game->player.pos.x + x_delta + float_sign(x_delta) * PL_RADIUS) / MAP_GRID_SIZE]))
		game->player.pos.x += x_delta;
	else
	{
		if (game->map->last_collision.x != game->player.pos.x && game->map->last_collision.y != game->player.pos.y)
			++(*collision);
		update_last_collision(game);
	}
	if (!is_wall(game->map->map[(int)(game->player.pos.y + y_delta + float_sign(y_delta) * PL_RADIUS) / MAP_GRID_SIZE]
				 [(int)game->player.pos.x / MAP_GRID_SIZE]))
		game->player.pos.y += y_delta;
	else
	{
		if (game->map->last_collision.x != game->player.pos.x && game->map->last_collision.y != game->player.pos.y)
			++(*collision);
		update_last_collision(game);
	}
	(void)collision;
}

void	check_borders(t_game *game)
{
	char	tile;

	tile = game->grid[(int) game->player.pos.y / MAP_GRID_SIZE][(int) game->player.pos.x / MAP_GRID_SIZE];
	if (is_wall(tile))
	{
		if ((game->player.pos.x - (int ) game->player.pos.x) - (game->player.pos.y - (int ) game->player.pos.y) > 0)
			game->player.pos.x -= game->player.delta.x;
		else
			game->player.pos.y -= game->player.delta.y;
	}
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
	check_borders(game);
}
