/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:28 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:18:07 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

// 0
void	start_game_scene(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	draw_hud(game);
	put_text_to_screen_layout(game->map->font, &game->img, &(t_text)
	{"kdancy and lsherry present", (t_vector){game->img.size.x / 2, game->hud
		.font_size / 2}, VTop | HCenter, 0xF0F0F0}, game->hud.font_size);
	if (game->pacman_logo.addr)
		put_image_to_image(&game->img,
			(t_vector){(game->img.size.x - game->pacman_logo.size.x) / 2,
			game->hud.font_size * 2}, &game->pacman_logo);
	put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x
			- game->img.size.x) / 2, 0}, &game->img);
	all_button_mouse_actions(game, game->pause.buttons, PAUSE_ENTRIES);
	all_button_actions(game, game->pause.buttons, PAUSE_ENTRIES);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window,
		game->hud_img.mlx_img, 0, 0);
	update_time(game);
}

// 1
void	pac_game_scene(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	check_aliveness(game);
	player_controll(game);
	cast_rays(game);
	enemy_move(game);
	update_volume(game);
	draw_ceil_floor_textured(game);
	draw_walls(game);
	draw_game_objects(game);
	draw_aim(game);
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
	game->show_map = false;
	change_all_enemies_cry_paused(game, 1);
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
	t_game		*game;

	game = __game;
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	draw_hud(game);
	put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x
			- game->img.size.x) / 2, 0}, &game->img);
	draw_rectangle_fill(&game->hud_img, (t_vector)
	{game->hud_img.size.x / 2 - game->img.size.x / 2, 0}, (t_vector)
	{game->img.size.x, game->img.size.y}, 0xA0000000);
	write_controls(game, game->hud.font_size,
		game->index_before_controls == PAUSE_MODE);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window,
		game->hud_img.mlx_img, 0, 0);
	update_time(game);
}