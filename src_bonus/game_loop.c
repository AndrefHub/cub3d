#include "../inc_bonus/cub3d_bonus.h"

void	put_frame(t_game *game)
{
	put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x - game->img.size.x) / 2, 0}, &game->img);
	if (game->show_map)
	{
		draw_map(game);
		put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x - game->img.size.x) / 2, 0}, &game->map->img);
	}
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->hud_img.mlx_img,
							0, 0);
}

void	player_win(t_game *game)
{
	static int c = 0;

	if (!c)
	{
		printf("You\'re winner!");
		++c;
	}
	(void)game;
}

float	ftorange(float val, float border)
{
	if (val < -border)
		val = -border;
	else if (val > border)
		val = border;
	return (val);
}

void	update_volume(t_game *game)
{
	t_list		*enemies;
	t_enemy		*enemy;
	t_fvector	pos;
	t_fvector	volume;
	float		angle;

	enemies = game->map->enemies;
	while (enemies)
	{
		enemy = enemies->content;
		pos = (t_fvector){game->player.pos.x - enemy->object->pos.x,
			game->player.pos.y - enemy->object->pos.y};
		angle = calculate_angle((t_fvector){1, 0}, pos);
		volume.x = ((cosf(angle - PI / 2) + 1) / 2) /
			fvector_distance(pos, (t_fvector){0, 0}) / 2;
		volume.y = ((cosf(angle + PI / 2) + 1) / 2) /
			fvector_distance(pos, (t_fvector){0, 0}) / 2;
		enemy->sound.play->volume0 += ftorange(volume.x - enemy->sound.play->volume0, 0.01);
		enemy->sound.play->volume1 += ftorange(volume.y - enemy->sound.play->volume1, 0.01);
		printf("l: %f, r: %f\n", enemy->sound.play->volume0, enemy->sound.play->volume1);
		enemies = enemies->next;
	}
}

int	game_loop(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
//	if (ft_lstsize(game->map->enemies) >= ft_lstsize(game->objects))
//		player_win(game);
//	else
	if (check_aliveness(game))
	{
		player_controll(game);
		cast_rays(game);
		enemy_move(game);

		draw_ceil_floor_textured(game);
		draw_walls(game);
		draw_game_objects(game);

		update_volume(game);

		draw_aim(game);

		draw_hud(game);
		put_frame(game);
		change_textures(game);
	}
	else
	{
		player_death(game);
	}
	update_time(game);
	return (0);
}