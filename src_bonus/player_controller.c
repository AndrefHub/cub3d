/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:24 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:50:29 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	player_delta_calculation(struct s_player *player)
{
	player->delta.x = cosf(player->angle) * PL_SPEED;
	player->delta.y = sinf(player->angle) * PL_SPEED;
}

void	mouse_controller(t_game *game)
{
	float	old_plane;

	if (game->key.mouse == true)
	{
		mouse_get_pos(game->mlx.id, game->mlx.window,
			&game->key.mpos.x, &game->key.mpos.y);
		game->key.mdir.x = game->key.mpos.x - game->mlx.win_size.x / 2;
		game->key.mdir.y = game->key.mpos.y - game->mlx.win_size.y / 2;
		mouse_move(game->mlx.id, game->mlx.window,
			game->mlx.win_size.x / 2, game->mlx.win_size.y / 2);
		game->z_offset += game->key.mdir.y * 2;
		game->player.angle += (float) game->key.mdir.x * PL_ROT_MOUSE_SPEED * 2;
		old_plane = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cosf((float)game->key
				.mdir.x * PL_ROT_MOUSE_SPEED * 2) - game->player.plane.y
			* sinf((float) game->key.mdir.x * PL_ROT_MOUSE_SPEED * 2);
		game->player.plane.y = old_plane * sinf((float) game->key.mdir.x
				* PL_ROT_MOUSE_SPEED * 2) + game->player.plane.y * cosf((float)
				game->key.mdir.x * PL_ROT_MOUSE_SPEED * 2);
		player_delta_calculation(&game->player);
	}
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
	mouse_controller(game);
	movement_controller(game);
	rotation_by_key_controller(game);
	check_restrictions(game);
	player_eat(game);
}
