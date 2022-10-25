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
        game->hud.font_size * 2);
	return (0);
}

int	selected_arrow_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	put_char_to_screen(game->map->font, &game->hud_img, &(t_text){"[",
		(t_vector){button->pos.x, button->text.pos.y - game->hud.font_size},
		HLeft | VBottom, PACMAN_COLOR}, game->hud.font_size * 2);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &button->text,
        game->hud.font_size * 2);
	return (0);
}

int	continue_button_func(void *__game, t_button *button)
{
	resume_game(__game);
	(void)button;
	return (0);
}

int	start_button_func(void *__game, t_button *button)
{
	resume_game(__game);
	change_button_to_pause_mode(__game);
	(void)button;
	return (0);
}

int	controls_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	set_game_input_mode(game, CONTROLS_MENU_MODE);
	(void)button;
	return (0);
}

int	exit_button_func(void *game, t_button *button)
{
	(void)button;
	error_exit(game, 0, "exit from menu");
	return (0);
}