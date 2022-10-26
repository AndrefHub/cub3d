#include "../inc_bonus/cub3d_bonus.h"

int	default_button_func(void *v, struct s_button *b)
{
	(void)v;
	(void)b;
	return (0);
}

int	selected_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	draw_rectangle_fill(&game->hud_img, button->pos, button->size,
		0x40b33f);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &button->text,
		game->hud.font_size * 1.5);
	return (0);
}

int	selected_arrow_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	put_char_to_screen(game->map->font, &game->hud_img, &(t_text){"[",
		(t_vector){button->pos.x, button->text.pos.y - game->hud.font_size
		+ game->mlx.win_size.y / 180},
		HLeft | VBottom, PACMAN_COLOR}, game->hud.font_size * 1.5);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &button->text,
		game->hud.font_size * 1.5);
	return (0);
}
