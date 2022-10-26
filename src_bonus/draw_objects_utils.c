#include "../inc_bonus/cub3d_bonus.h"

int	object_comparator(t_object *obj1, t_object *obj2)
{
	return (obj1->distance < obj2->distance);
}

void	update_distance(t_game *game)
{
	t_list		*elem;
	t_object	*obj;

	elem = game->objects;
	while (elem)
	{
		obj = elem->content;
		obj->distance = fvector_distance(game->player.pos, obj->pos);
		elem = elem->next;
	}
}
