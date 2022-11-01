#include "../inc_bonus/cub3d_bonus.h"

void	set_game_input_mode(t_game *game, int mode)
{
	game->input_mode = mode;
	game->scene.scene_func = game->scene_funcs[game->input_mode];
}

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

void	stop_respawn(t_game *game)
{
	set_game_input_mode(game, LEADERBOARD_MODE);
}

void	end_game_dim(t_game *game)
{	
	static int		i = 0;
	static t_ull	time = 0;

	if (!i)
	{
		game->show_map = 0;
		change_all_enemies_cry_paused(game, 1);
		cs_play_sound(game->audio.ctx, game->audio.sounds[DEATH_SOUND].def);
	}
	if (i < 50 && get_time() - time > 35)
	{
		time = get_time();
		dim_screen(game, i);
		++i;
	}
	else if (i == 50)
	{
		if (player_respawn(game, &i, &time))
			return ;
		game->player_lb_data->score_num = game->hud.score.value_numeric;
		ft_lst_insert(&game->leaderboard,
			ft_lstnew(game->player_lb_data), cmp_lb_entry);
		++i;
	}
	if (i > 50)
		put_ended_game_image(game);
}
