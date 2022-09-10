#include "../inc_bonus/cub3d_bonus.h"

void	draw_hud(t_game *game, t_ull time1, t_ull time2)
{
	mlx_string_put(game->mlx.id, game->mlx.window, 60, 15, 0x00FFFFFF, \
		(char []){'0' + time1 / 1000, '0' + time1 / 100 % 10, '0' + time1 / 10 % 10, '0' + time1 % 10, '\0'});
	mlx_string_put(game->mlx.id, game->mlx.window, 120, 15, 0x00FFFFFF, \
		(char []){'0' + time2 / 1000, '0' + time2 / 100 % 10, '0' + time2 / 10 % 10, '0' + time2 % 10, '\0'});
}

int	game_loop(t_game *game)
{
	player_controll(game);
	enemy_move(game);
	fill_img_color(&game->img, 0x808080);
	fill_ceiling_color(&game->img, game->map->C, game->horizon);
	draw_ceil_textured(game);
	fill_floor_color(&game->img, game->map->F, game->horizon);
//	draw_player(game);
//	printf("HORIZON: %d\n", game->horizon);
	t_ull time = get_time();
	cast_rays(game);
	t_ull time_rays = get_time() - time;
	time = get_time();
	draw_walls(game);
	t_ull time_drawing = get_time() - time;

	draw_aim(game);

	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img,
							0, 0);
	if (game->show_map)
		draw_map(game);
	draw_hud(game, time_rays, time_drawing);
	draw_fps(game);
	change_textures(game);
	game->time.last = get_time();
	return (0);
}