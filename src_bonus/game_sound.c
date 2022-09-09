#include "../inc_bonus/cub3d_bonus.h"

void	set_sound(t_sound *sound, char *filename)
{
	sound->file = cs_load_wav(filename);
	sound->def = cs_make_def(&sound->file);
	sound->def.volume_left = 1.f;
	sound->def.volume_right = 1.f;
}

void	init_main_game_sound_theme(t_game *game, char *main_music_theme_filename)
{
	game->audio.ctx = cs_make_context(0, 44100, 4096, 4, NULL);
	cs_spawn_mix_thread(game->audio.ctx);
	cs_thread_sleep_delay(game->audio.ctx, 5);

	game->audio.song.file = cs_load_wav(main_music_theme_filename);
	if (game->audio.song.file.channels[0])
	{
		game->audio.song.def = cs_make_def(&game->audio.song.file);
		game->audio.song.def.looped = 1;
	}
}

void	set_game_events_sounds(struct s_audio *audio, char *filename)
{
	set_sound(&audio->bonk, filename);
}