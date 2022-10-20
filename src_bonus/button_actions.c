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

int	continue_button_func(void *__game, t_button *button)
{
	resume_game(__game);
	(void)button;
	return (0);
}

int	controls_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	game->scene.scene_func = (void *)controls_game_scene;
	game->input_mode = CONTROLS_MENU_MODE;
	(void)button;
	return (0);
}

int	exit_button_func(void *game, t_button *button)
{
	(void)button;
	error_exit(game, 0, "exit from menu");
	return (0);
}