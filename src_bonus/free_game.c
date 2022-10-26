#include "../inc_bonus/cub3d_bonus.h"

void	free_sound(t_game *game)
{
	cs_free_sound(&game->audio.bonk.file);
	cs_free_sound(&game->audio.song.file);
}

void	free_texture_lists(t_game *game)
{
	int	i;

	i = -1;
	while (++i < MAX_WALL_CHARS)
		ft_lstclear(&game->map->walls[i].texture, free);
}
