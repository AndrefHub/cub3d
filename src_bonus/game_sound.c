#include "../inc_bonus/cub3d_bonus.h"

void	set_sound(t_sound *sound, char *filename)
{
	sound->file = cs_load_wav(filename);
	printf("%s %p %p\n", filename, sound->file.channels[0], sound->file.channels[1]);
	copy_sound(sound, sound);
}

void	copy_sound(t_sound *sound, t_sound *src)
{
	 if (!src->file.channels[0])
	 {
	 	error_exit(NULL, 1, "Sound file not found");
	 }
	sound->def = cs_make_def(&src->file);
	// sound->def.looped = 1;
}

void	init_main_game_sound(t_game *game)
{
	game->audio.ctx = cs_make_context(0, 44100, 4096, 8, NULL);
	cs_spawn_mix_thread(game->audio.ctx);
	cs_thread_sleep_delay(game->audio.ctx, 5);
}

void	set_game_events_sounds(struct s_audio *audio, char **sounds)
{
	int	counter;

	counter = -1;
	while (++counter < MAX_SOUNDS)
		set_sound(&audio->sounds[counter], sounds[counter]);
}
