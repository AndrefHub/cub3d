#include "../inc/cub3d_bonus.h"

void	free_sound(t_game *game)
{
	cs_free_sound(&game->sound.file);
	cs_free_sound(&game->sound.song_file);
}