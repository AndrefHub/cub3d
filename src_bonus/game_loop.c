#include "../inc_bonus/cub3d_bonus.h"


int	game_loop(t_game *game)
{
	player_controll(game);
//	enemy_move(game);
	fill_img_color(&game->img, 0x808080);
//	fill_floor_color(&game->img, game->map->F);
//	fill_ceiling_color(&game->img, game->map->C);
//	draw_player(game);
//  draw_hud(game);
	t_ull time = get_time();
	cast_rays(game);
	printf("--- %llu --- ", get_time() - time);
	time = get_time();
	draw_walls(game);
	printf("%llu --- \n", get_time() - time);

//	draw_aim(game);

	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img,
							0, 0);
//	if (game->show_map)
//		draw_map(game);
	draw_fps(game);
//	change_textures(game);
	game->time.last = get_time();
	return (0);
}