#include "../inc_bonus/cub3d_bonus.h"

void	put_frame(t_game *game)
{
	put_image_to_image(&game->img, (t_vector){0, 0}, &game->hud_img);
	if (game->show_map)
		draw_map(game);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img,
							0, 0);
}

int	game_loop(t_game *game)
{
	fill_img_color(&game->hud_img, 0xFF000000);
	if (check_aliveness(game))
	{
		player_controll(game);
		enemy_move(game);

		fill_ceiling_color(&game->img, game->map->c, game->z_offset);
		fill_floor_color(&game->img, game->map->f, game->z_offset);
		draw_ceil_floor_textured(game);

		cast_rays(game);
		draw_walls(game);
		draw_game_objects(game);

		draw_aim(game);

//		draw_fps(game);
		draw_hud(game);
		put_frame(game);
		change_textures(game);
	}
	else
	{
		player_death(game);
	}
	update_time(game);
	// draw_hud(game, time_rays, time_drawing);
	// game->time.last = get_time();
	return (0);
}