#include "../inc_bonus/cub3d_bonus.h"

void	put_frame(t_game *game)
{
	put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x - game->img.size.x) / 2, 0}, &game->img);
	if (game->show_map)
	{
		draw_map(game);
		put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x - game->img.size.x) / 2, 0}, &game->map->img);
	}
	put_image_to_image(&game->main_img, (t_vector){0, 0}, &game->hud_img);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->main_img.mlx_img,
							0, 0);
}

int	game_loop(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	if (check_aliveness(game))
	{
		player_controll(game);
		enemy_move(game);
		draw_ceil_floor_textured(game);

		cast_rays(game);
		draw_walls(game);
		draw_game_objects(game);

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