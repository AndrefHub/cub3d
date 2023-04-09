/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_scenes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:32 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:18:17 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	set_game_input_mode(t_game *game, int mode)
{
	game->input_mode = mode;
	game->scene.scene_func = game->scene_funcs[game->input_mode];
	set_game_audio_input_mode(game, mode);
}

void	stop_respawn(t_game *game)
{
	set_game_input_mode(game, LEADERBOARD_MODE);
}

void	end_game_dim(t_game *game)
{	
	static int		i = 0;
	static t_ull	time = 0;

	if (get_time() - time > 35 && i < 50)
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

void	write_controls(t_game *game, int font_size, int flag)
{
	const int	y = game->hud_img.size.y / (3 * (1 + flag));
	int			c;

	c = 0;
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{"controls", (t_vector){game->hud_img.size.x / 2, y - font_size},
		VCenter | HCenter, 0xE0E0E0}, font_size * 1.5);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{"WASD - MOVE PLAYER", (t_vector){game->hud_img.size.x / 2,
		y + 2 * font_size * (++c)}, VCenter | HCenter, 0xE0E0E0}, font_size);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{"LEFT/RIGHT/MOUSE - ROTATE PLAYER", (t_vector){game->hud_img.size.x / 2,
		y + 2 * font_size * (++c)}, VCenter | HCenter, 0xE0E0E0}, font_size);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{"E - OPEN DOORS", (t_vector){game->hud_img.size.x / 2,
		y + 2 * font_size * (++c)}, VCenter | HCenter, 0xE0E0E0}, font_size);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{"M - OPEN MAP", (t_vector){game->hud_img.size.x / 2,
		y + 2 * font_size * (++c)}, VCenter | HCenter, 0xE0E0E0}, font_size);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{"ESC - PAUSE/UNPAUSE GAME", (t_vector){game->hud_img.size.x / 2,
		y + 2 * font_size * (++c)}, VCenter | HCenter, 0xE0E0E0}, font_size);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{"ENTER/RIGHT CLICK - CONFIRM", (t_vector){game->hud_img.size.x / 2,
		y + 2 * font_size * (++c)}, VCenter | HCenter, 0xE0E0E0}, font_size);
}
