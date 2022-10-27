#include "../inc_bonus/cub3d_bonus.h"

void	put_frame(t_game *game)
{
	draw_hud(game);
	put_image_to_image(&game->hud_img, (t_vector)
	{(game->mlx.win_size.x - game->img.size.x) / 2, 0}, &game->img);
	if (game->show_map)
	{
		draw_map(game);
		put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x
				- game->img.size.x) / 2, 0}, &game->map->img);
	}
	mlx_put_image_to_window(game->mlx.id, game->mlx.window,
		game->hud_img.mlx_img, 0, 0);
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
		if (enemy->sound.play)
		{
			pos = (t_fvector){game->player.pos.x - enemy->object->pos.x,
				game->player.pos.y - enemy->object->pos.y};
			angle = calculate_angle((t_fvector){1, 0}, pos);
			volume = (t_fvector){((cosf(angle - PI / 2) + 1) / 2) / distancef
				(&pos, &(t_fvector){0, 0}) / 2, ((cosf(angle + PI / 2) + 1) / 2)
				/ distancef(&pos, &(t_fvector){0, 0}) / 2};
			enemy->sound.play->volume0 += ftorange
				(volume.x - enemy->sound.play->volume0, 0.01);
			enemy->sound.play->volume1 += ftorange
				(volume.y - enemy->sound.play->volume1, 0.01);
		}
		enemies = enemies->next;
	}
}

int	game_loop(t_scene *scene)
{
	scene->scene_func(scene->parameter);
	return (0);
}
