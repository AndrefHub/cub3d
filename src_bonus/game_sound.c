/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:34 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:11:39 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	set_sound(t_sound *sound, char *filename)
{
	sound->file = cs_load_wav(filename);
	copy_sound(sound, sound);
}

void	copy_sound(t_sound *sound, t_sound *src)
{
	if (!src->file.channels[0])
		error_exit(NULL, 1, "Sound file not found");
	sound->def = cs_make_def(&src->file);
}

void	init_main_game_sound(struct s_audio *audio)
{
	audio->ctx = cs_make_context(0, 44100, 4096, 32, NULL);
	cs_spawn_mix_thread(audio->ctx);
	cs_thread_sleep_delay(audio->ctx, 5);
}

void	set_game_events_sounds(struct s_audio *audio, char **sounds)
{
	int	counter;

	counter = -1;
	while (++counter < MAX_SOUNDS)
		set_sound(&audio->sounds[counter], sounds[counter]);
}
