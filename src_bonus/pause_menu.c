#include "../inc_bonus/cub3d_bonus.h"

// void	print_selected_entry_frame(t_game *game, t_text *text)
// {

// }

int	selected_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	draw_rectangle_fill(&game->hud_img, button->pos, button->size,
		0x40b33f);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &button->text, 30);
	return (0);
}

int	continue_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	game->scene.scene_func = (void *)pac_game_scene;
	game->input_mode = GAME_MODE;
	return (0);
}

void	controls_game_scene(void *__game)
{
	const int	font_size = 60;
	t_game		*game;

	game = __game;
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	draw_hud(game);
	put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x
	- game->img.size.x) / 2, 0}, &game->img);
	
	draw_rectangle_fill(&game->hud_img, (t_vector){game->hud_img.size.x / 2 -
		game->img.size.x / 2, 0}, (t_vector){game->img.size.x, game->img.size.y}
		, 0xA0000000);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text){
		"controls", (t_vector){game->hud_img.size.x / 2, font_size}, 
		VCenter | HCenter, 0xE0E0E0}, font_size);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text){
		"just move bro", (t_vector){game->hud_img.size.x / 2, 3 * font_size},
		VCenter | HCenter, 0xE0E0E0}, font_size);

	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->hud_img.mlx_img,
							0, 0);
	update_time(game);
}

int	controls_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	game->scene.scene_func = (void *)controls_game_scene;
	game->input_mode = GAME_MODE;
	return (0);
}

int	exit_button_func(void *game, t_button *button)
{
	(void)button;
	error_exit(game, 0, "exit from menu");
	return (0);
}

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

void	all_button_actions(t_game *game, t_button *buttons, int size)
{
	int	counter;

	counter = -1;
	while (++counter < size)
	{
		button_actions(game, buttons + counter);
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
	all_button_actions(game, game->pause.buttons, PAUSE_ENTRIES);
}