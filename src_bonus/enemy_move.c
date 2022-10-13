#include "../inc_bonus/cub3d_bonus.h"

t_list	*pathfinding_algo_straight(t_game *game, t_enemy *enemy)
{
	t_vector	en;

	en = (t_vector){enemy->object->pos.x, enemy->object->pos.y};
	if (0 < en.x && en.x < game->map->map_size.x - 1 && 0 < en.y
		&& en.y < game->map->map_size.y - 1)
		return (get_first_n_nodes(astar(game, en, (t_vector){game->player.pos.x,
		game->player.pos.y}), 5));
	return (NULL);
}