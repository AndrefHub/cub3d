#include "../inc/cub3d.h"

void	player_delta_calculation(struct s_player *player)
{
	player->delta.x = cosf(player->angle) * PL_SPEED;
	player->delta.y = sinf(player->angle) * PL_SPEED;
}

void	movement_controller(t_game *game)
{
	if (key_pressed(game, W_KEY))
		move_radius_check(game, game->player.delta.x, game->player.delta.y);
	if (key_pressed(game, S_KEY))
		move_radius_check(game, -game->player.delta.x, -game->player.delta.y);
	if (key_pressed(game, D_KEY))
		move_radius_check(game, -game->player.delta.y, game->player.delta.x);
	if (key_pressed(game, A_KEY))
		move_radius_check(game, game->player.delta.y, -game->player.delta.x);
}

void	rotation_by_key_controller(t_game *game)
{
	float	old_plane;

	if (key_pressed(game, RIGHT_KEY) || key_pressed(game, E_KEY))
	{
		game->player.angle += PL_ROT_KEY_SPEED;
		old_plane = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cosf(PL_ROT_KEY_SPEED)
			- game->player.plane.y * sinf(PL_ROT_KEY_SPEED);
		game->player.plane.y = old_plane * sinf(PL_ROT_KEY_SPEED)
			+ game->player.plane.y * cosf(PL_ROT_KEY_SPEED);
	}
	if (key_pressed(game, LEFT_KEY) || key_pressed(game, Q_KEY))
	{
		game->player.angle -= PL_ROT_KEY_SPEED;
		old_plane = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cosf(-PL_ROT_KEY_SPEED)
			- game->player.plane.y * sinf(-PL_ROT_KEY_SPEED);
		game->player.plane.y = old_plane * sinf(-PL_ROT_KEY_SPEED)
			+ game->player.plane.y * cosf(-PL_ROT_KEY_SPEED);
	}
	player_delta_calculation(&game->player);
}

void	player_controll(t_game *game)
{
	movement_controller(game);
	rotation_by_key_controller(game);
	check_restrictions(game);
}
