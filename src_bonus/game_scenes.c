#include "../inc_bonus/cub3d_bonus.h"

// 1
void	pac_game_scene(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	check_aliveness(game);
	player_controll(game);
	cast_rays(game);
	enemy_move(game);
	draw_ceil_floor_textured(game);
	draw_walls(game);
	draw_game_objects(game);
	draw_aim(game);
	draw_hud(game);
	put_frame(game);
	change_textures(game);
	update_time(game);
	if (edibles_eaten(game))
	{
		game->death_func = draw_afterdeath_animation;
		set_game_input_mode(game, WIN_SCREEN_MODE);
	}
}

// 2
void	leaderboard_game_scene(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	put_ended_game_image(game);
	update_time(game);
}

// 3
void	win_game_scene(void *_game)
{
	t_game	*game;

	game = _game;
	game->death_func(game);
}

// 4
void	pause_game_scene(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	draw_hud(game);
	put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x
			- game->img.size.x) / 2, 0}, &game->img);
	print_pause_menu_entries(game);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window,
		game->hud_img.mlx_img, 0, 0);
	update_time(game);
}

// 5
void	controls_game_scene(void *__game)
{
	const int	font_size = 60;
	t_game		*game;

	game = __game;
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	draw_hud(game);
	put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x
			- game->img.size.x) / 2, 0}, &game->img);
	draw_rectangle_fill(&game->hud_img, (t_vector)
	{game->hud_img.size.x / 2 - game->img.size.x / 2, 0}, (t_vector)
	{game->img.size.x, game->img.size.y}, 0xA0000000);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{"controls", (t_vector){game->hud_img.size.x / 2, font_size},
		VCenter | HCenter, 0xE0E0E0}, font_size);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{"just move bro", (t_vector){game->hud_img.size.x / 2, 3 * font_size},
		VCenter | HCenter, 0xE0E0E0}, font_size);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window,
		game->hud_img.mlx_img, 0, 0);
	update_time(game);
}
