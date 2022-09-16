#include "../inc_bonus/cub3d_bonus.h"

void	draw_hud(t_game *game, t_ull time1, t_ull time2)
{
	mlx_string_put(game->mlx.id, game->mlx.window, 40, 15, 0x00FFFFFF,
				   "tr:");
	mlx_string_put(game->mlx.id, game->mlx.window, 60, 15, 0x00FFFFFF, \
		(char []){'0' + time1 / 1000, '0' + time1 / 100 % 10, '0' + time1 / 10 % 10, '0' + time1 % 10, '\0'});
	mlx_string_put(game->mlx.id, game->mlx.window, 100, 15, 0x00FFFFFF,
				   "td:");
	mlx_string_put(game->mlx.id, game->mlx.window, 120, 15, 0x00FFFFFF, \
		(char []){'0' + time2 / 1000, '0' + time2 / 100 % 10, '0' + time2 / 10 % 10, '0' + time2 % 10, '\0'});
}

int	game_loop(t_game *game)
{
	t_ull time_rays = -1;
	t_ull time_drawing = -1;

	if (check_aliveness(game))
	{
		player_controll(game);
		enemy_move(game);
		fill_img_color(&game->img, 0x808080);
		fill_ceiling_color(&game->img, game->map->C, game->z_offset);
		draw_ceil_textured(game);
		fill_floor_color(&game->img, game->map->F, game->z_offset);
	//	draw_player(game);
		// t_ull time = get_time();
		cast_rays(game);	
		// time_rays = get_time() - time;
		// time = get_time();
		draw_walls(game);
		// time_drawing = get_time() - time;
		// printf("*** %llu *** %llu ***\n", time_rays, time_drawing);
		draw_aim(game);
		mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img,
								0, 0);
		if (game->show_map)
			draw_map(game);

		change_textures(game);
	}
	else 
	{
		player_death(game);
	}
	draw_hud(game, time_rays, time_drawing);
	draw_fps(game);
	game->time.last = get_time();
	return (0);
}