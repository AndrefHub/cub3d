#include "../inc_bonus/cub3d_bonus.h"

void	draw_hud_entry(t_game *game, t_hud_entry *entry, int y)
{
	t_vector	text_pos;

	text_pos = (t_vector){game->mlx.win_size.x - (game->mlx.win_size.x -
		game->img.size.x) / 2 + ((game->mlx.win_size.x - game->img.size.x)
		/ 2) / 1.9, game->hud.font_size * y};
	ft_bzero(entry->value, entry->value_size);
	entry->value_numeric %= 1 << 24;
	// if (entry->value_numeric >= (1 << 16))
		// ft_strlcat(output, "NAN", 4);
	// else
	ft_put_itoa(entry->value, entry->value_numeric);
	put_text_to_screen_layout(game, &game->hud_img, &(t_text){
		entry->title, (t_vector)
		{text_pos.x,text_pos.y}, VTop | HCenter, 0xDFEFEF}, game->hud.font_size); //TODO: put title and value on different strings
	put_text_to_screen_layout(game, &game->hud_img, &(t_text){entry->value, (t_vector)
		{text_pos.x, text_pos.y + game->hud.font_size * 1.5f},
		VTop | HCenter, 0xDFEFEF}, game->hud.font_size);
}

void	draw_hud(t_game *game)
{
	int	y;

	y = 2;
	put_image_to_image(&game->hud_img, (t_vector) {0, 0}, &game->hud_texture);
	draw_hud_entry(game, &game->hud.fps, ++y * 3);
	draw_hud_entry(game, &game->hud.score, ++y * 3);
	draw_hud_entry(game, &game->hud.lives, ++y * 3);
	draw_hud_entry(game, &game->hud.health, ++y * 3);
}