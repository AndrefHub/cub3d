#include "../inc_bonus/cub3d_bonus.h"

void	player_delta_calculation(struct s_player *player)
{
	player->delta.x = cosf(player->angle) * 0.05f;
	player->delta.y = sinf(player->angle) * 0.05f;
}

void	mouse_controller(t_game *game)
{
	if (game->key.mouse == true)
	{
		mouse_get_pos(game->mlx.id, game->mlx.window, &game->key.mpos.x,&game->key.mpos.y);
		game->key.mdir.x = game->key.mpos.x - game->img.size.x / 2;
		game->key.mdir.y = game->key.mpos.y - game->img.size.y / 2;
		mouse_move(game->mlx.id, game->mlx.window, game->img.size.x / 2, game->img.size.y / 2);
		game->z_offset += (float) game->key.mdir.y * 2;
		game->player.angle += (float) game->key.mdir.x * PL_ROT_MOUSE_SPEED * 2;
		player_delta_calculation(&game->player);
	}
}

void	movement_controller(t_game *game, int *collision)
{
	// if (key_pressed(game, LEFT_CTRL_KEY))
	// {
	// 	game->player.delta.x *= PL_ACCELERATION;
	// 	game->player.delta.y *= PL_ACCELERATION;
	// }
	if (key_pressed(game, W_KEY))
		move_radius_check(game, game->player.delta.x, game->player.delta.y, collision);
	if (key_pressed(game, S_KEY))
		move_radius_check(game, -game->player.delta.x, -game->player.delta.y, collision);
	if (key_pressed(game, D_KEY))
		move_radius_check(game, -game->player.delta.y, game->player.delta.x, collision);
	if (key_pressed(game, A_KEY))
		move_radius_check(game, game->player.delta.y, -game->player.delta.x, collision);
}

void	rotation_by_key_controller(t_game *game)
{
	if (key_pressed(game, RIGHT_KEY))
		game->player.angle += PL_ROT_KEY_SPEED;
	if (key_pressed(game, LEFT_KEY))
		game->player.angle -= PL_ROT_KEY_SPEED;
	player_delta_calculation(&game->player);
}

void	player_controll(t_game *game)
{
	int collision = 0;

	mouse_controller(game);
	movement_controller(game, &collision);
	rotation_by_key_controller(game);
	if (collision)
	{
		cs_play_sound(game->audio.ctx, game->audio.bonk.def);
		update_last_collision(game);
	}
	check_restrictions(game);
}
