#include "../inc_bonus/cub3d_bonus.h"

void	draw_hud_entry(t_game *game, t_hud_entry *entry, int offset, int y)
{
	const int font_size = 20;
	char	*output;

	output = entry->title + offset;
	ft_bzero(output, entry->title_size - offset);
	ft_put_itoa(output, entry->value);
	put_text_to_screen_layout(game, &(t_text){
		entry->title, (t_vector){0, font_size * y}, VTop | HLeft
		}, font_size
	);
}

void	draw_hud(t_game *game)
{
	int	y;

	y = -1;
	draw_hud_entry(game, &game->hud.fps, game->hud.fps.title_size, ++y);
	draw_hud_entry(game, &game->hud.score, game->hud.score.title_size, ++y);
	// mlx_string_put(game->mlx.id, game->mlx.window, 40, 15, 0x00FFFFFF,
	// 			   "tr:");
	// mlx_string_put(game->mlx.id, game->mlx.window, 60, 15, 0x00FFFFFF, 
	// 	(char []){'0' + time1 / 1000, '0' + time1 / 100 % 10, '0' + time1 / 10 % 10, '0' + time1 % 10, '\0'});
	// mlx_string_put(game->mlx.id, game->mlx.window, 100, 15, 0x00FFFFFF,
	// 			   "td:");
	// mlx_string_put(game->mlx.id, game->mlx.window, 120, 15, 0x00FFFFFF, 
	// 	(char []){'0' + time2 / 1000, '0' + time2 / 100 % 10, '0' + time2 / 10 % 10, '0' + time2 % 10, '\0'});
}