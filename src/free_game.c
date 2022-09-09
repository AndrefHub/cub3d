#include "../inc/cub3d.h"


void	free_texture_lists(t_game *game)
{
	int	i;

	i = -1;
	while (++i < MAX_WALL_CHARS)
		ft_lstclear(&game->map->walls[i].texture, free);
	
}