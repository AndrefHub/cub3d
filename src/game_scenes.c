#include "../inc/cub3d.h"

// 1
void	pac_game_scene(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	player_controll(game);
	cast_rays(game);
	draw_ceil_floor_textured(game);
	draw_walls(game);
	draw_aim(game);
	put_frame(game);
}
