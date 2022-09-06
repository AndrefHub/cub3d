#include "../inc/cub3d.h"

void	free_sound(t_game *game)
{
	cs_free_sound(&game->audio.bonk.file);
	cs_free_sound(&game->audio.song.file);
}

void	free_texture_lists(t_game *game)
{
	int	i;

	i = -1;
	while (++i < MAX_TEXTURES)
		ft_lstclear(&game->map->texture_list[i], free);
	
}