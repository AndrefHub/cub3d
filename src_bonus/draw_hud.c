#include "../inc_bonus/cub3d_bonus.h"

void	draw_hud_entry(t_game *game, t_hud_entry *entry, int offset, int y)
{
	char		*output;
	t_vector	text_pos;

	text_pos = (t_vector) {game->mlx.win_size.x - (game->mlx.win_size.x - game->img.size.x) / 2 + ((game->mlx.win_size.x - game->img.size.x) / 2) / 4,
						   game->hud.font_size * y};
	output = entry->title + offset;
	ft_bzero(output, entry->title_size - offset);
	ft_put_itoa(output, entry->value);
	put_text_to_screen_layout(game, &(t_text){
		entry->title, (t_vector)
		{text_pos.x,text_pos.y}, VTop | HLeft}, game->hud.font_size); //TODO: put title and value on different strings
	put_text_to_screen_layout(game, &(t_text){
			output, (t_vector)
					{text_pos.x,
					 text_pos.y + game->hud.font_size * 1.5f}, VTop | HLeft}, game->hud.font_size);
}

void	draw_hud(t_game *game)
{
	int	y;

	y = 2;
//	fill_img_color(&game->hud_img, 0x000000);
	put_image_to_image(&game->hud_img, (t_vector) {0, 0}, &game->hud_texture);
	draw_hud_entry(game, &game->hud.fps, game->hud.fps.title_size, ++y * 3);
	draw_hud_entry(game, &game->hud.score, game->hud.score.title_size, ++y * 3);
	draw_hud_entry(game, &game->hud.lives, game->hud.lives.title_size, ++y * 3);
	draw_hud_entry(game, &game->hud.health, game->hud.health.title_size, ++y * 3);
//	put_text_to_screen_layout(game, &(t_text){
//		"a", (t_vector){game->mlx.win_size.x - (game->mlx.win_size.x - game->img.size.x) / 2, 30 * ++y}, VTop | HLeft
//		}, 120
//	);
	// mlx_string_put(game->mlx.id, game->mlx.window, 40, 15, 0x00FFFFFF,
	// 			   "tr:");
	// mlx_string_put(game->mlx.id, game->mlx.window, 60, 15, 0x00FFFFFF, 
	// 	(char []){'0' + time1 / 1000, '0' + time1 / 100 % 10, '0' + time1 / 10 % 10, '0' + time1 % 10, '\0'});
	// mlx_string_put(game->mlx.id, game->mlx.window, 100, 15, 0x00FFFFFF,
	// 			   "td:");
	// mlx_string_put(game->mlx.id, game->mlx.window, 120, 15, 0x00FFFFFF, 
	// 	(char []){'0' + time2 / 1000, '0' + time2 / 100 % 10, '0' + time2 / 10 % 10, '0' + time2 % 10, '\0'});
}