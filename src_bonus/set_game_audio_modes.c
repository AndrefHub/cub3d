/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_audio_modes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:39 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:19:41 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

// mode = GAME_MODE
void	set_game_audio_game(t_game *game)
{
	static int	i = 0;

	if (!i)
	{
		pause_all_sounds(game);
		play_t_sound(game->audio.ctx, &game->audio.sounds[START_SOUND]);
		++i;
	}
	change_all_enemies_cry_paused(game, 0);
}

// mode = LEADERBOARD_MODE
void	set_game_audio_leaderboard(t_game *game)
{
	(void)game;
}

// mode = WIN_SCREEN_MODE
void	set_game_audio_win_screen(t_game *game)
{
	pause_all_sounds(game);
	if (edibles_eaten(game))
		play_t_sound(game->audio.ctx, &(game->audio.sounds[WIN_SOUND]));
	else
		play_t_sound(game->audio.ctx, &(game->audio.sounds[DEATH_SOUND]));
}

// mode = PAUSE_MODE
void	set_game_audio_pause(t_game *game)
{
	pause_all_sounds(game);
	play_t_sound(game->audio.ctx, &(game->audio.sounds[PAUSE_SOUND]));
}

// mode = CONTROLS_MENU_MODE
void	set_game_audio_controls(t_game *game)
{
	(void)game;
}
