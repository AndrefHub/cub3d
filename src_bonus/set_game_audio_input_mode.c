/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_audio_input_mode.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:39 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 19:29:26 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void    play_t_sound(cs_context_t *ctx, t_sound *sound)
{
    sound->play = cs_play_sound(ctx, sound->def);
}

void    pause_all_sounds(t_game *game)
{
    int i;

    i = -1;
    while (++i < MAX_SOUNDS)
    {
        if (game->audio.sounds->play)
            game->audio.sounds->play->paused = 1;
    }
    change_all_enemies_cry_paused(game, 1);
}

void	set_game_audio_input_mode(t_game *game, int mode)
{
    pause_all_sounds(game);
    if (mode == START_MODE)
        set_game_audio_start(game);
    else if (mode == GAME_MODE)
        set_game_audio_game(game);
	else if (mode == LEADERBOARD_MODE)
		set_game_audio_leaderboard(game);
	else if (mode == WIN_SCREEN_MODE)
		set_game_audio_win_screen(game);
	else if (mode == PAUSE_MODE)
		set_game_audio_pause(game);
	else if (mode == CONTROLS_MENU_MODE)
		set_game_audio_controls(game);
}

// mode = START_GAME;
void    set_game_audio_start(t_game *game)
{
    play_t_sound(game->audio.ctx, &(game->audio.sounds[INTRO_SOUND]));
}

// mode = GAME_MODE
void    set_game_audio_game(t_game *game)
{
    change_all_enemies_cry_paused(game, 0);
}

// mode = LEADERBOARD_MODE
void    set_game_audio_leaderboard(t_game *game)
{

}

// mode = WIN_SCREEN_MODE
void    set_game_audio_win_screen(t_game *game)
{
    if (edibles_eaten(game))
        play_t_sound(game->audio.ctx, &(game->audio.sounds[WIN_SOUND]));
    else
        play_t_sound(game->audio.ctx, &(game->audio.sounds[DEATH_SOUND]));
}

// mode = PAUSE_MODE
void    set_game_audio_pause(t_game *game)
{
    if (edibles_eaten(game))
        play_t_sound(game->audio.ctx, &(game->audio.sounds[WIN_SOUND]));
    else
        play_t_sound(game->audio.ctx, &(game->audio.sounds[DEATH_SOUND]));
}

// mode = CONTROLS_MENU_MODE
void    set_game_audio_controls(t_game *game)
{
    if (edibles_eaten(game))
        play_t_sound(game->audio.ctx, &(game->audio.sounds[WIN_SOUND]));
    else
        play_t_sound(game->audio.ctx, &(game->audio.sounds[DEATH_SOUND]));
}
