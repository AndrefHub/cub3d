#include "../inc_bonus/cub3d_bonus.h"

t_list	*pathfinding_algo_straight(t_game *game, t_enemy *enemy)
{
	return (astar(game, (t_vector){enemy->object->pos.x, enemy->object->pos.y},
			(t_vector){game->player.pos.x, game->player.pos.y}));
}