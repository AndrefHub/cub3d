#include "../inc_bonus/cub3d_bonus.h"

// void	print_selected_entry_frame(t_game *game, t_text *text)
// {

// }
void	show_button(t_img *img, t_texture *font, t_button *button)
{
	draw_rectangle_fill(img, button->pos, button->size,
		*((int *)&button->background_color));
	put_text_to_screen_layout(font, img, &button->text, 30);
	(void)font;
}

void	show_buttons(t_img *img, t_texture *font, t_button *buttons, int size)
{
	int counter;

	counter = -1;
	while (++counter < size)
	{
		show_button(img, font, buttons + counter);
	}
}

void	print_pause_menu_entries(t_game *game)
{
	const int	font_size = 60;
	
	draw_rectangle_fill(&game->hud_img, (t_vector){game->hud_img.size.x / 2 -
		game->img.size.x / 2, 0}, (t_vector){game->img.size.x, game->img.size.y}
		, 0xA0000000);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text){"PAUSE"
		, (t_vector){game->hud_img.size.x / 2, font_size}, VCenter | HCenter, 0xE0E0E0}, font_size);
	show_buttons(&game->hud_img, game->map->font, game->pause.buttons,
		PAUSE_ENTRIES);
}