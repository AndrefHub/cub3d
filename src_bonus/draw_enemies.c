#include "../inc_bonus/cub3d_bonus.h"

int	object_comparator(t_object *obj1, t_object *obj2)
{
	return (obj1->distance < obj2->distance);
}

void	draw_object(t_game *game, t_object *object)
{
	t_fvector	sprite;
	t_vector	start;
	t_vector	end;
	t_vector size;


	sprite = (t_fvector) {object->pos.x - game->player.pos.x, object->pos.y - game->player.pos.y};
	size.y = (int) (ABS_WALL_SIZE / object->distance);
	printf("%d\n", size.y);
	size.x = size.y;
	float angle_to_player = atan2f(sprite.y, sprite.x) - game->player.angle;
	if (angle_to_player < -PI)
		angle_to_player += 2 * PI;
	start.x = (game->img.size.x / 2) + tanf(angle_to_player) /
			0.001f - size.x / 2;
	start.y = (game->img.size.y / 2) - game->z_offset;
	end.x = start.x + size.x;
	end.y = start.y + size.y;


	if (start.x > 0)
	{
		draw_square_fill(&game->img, start, size.y, 0);
		draw_line(&game->img, start, end, AIM_COLOR);
	}

}

void	draw_game_objects(t_game *game)
{
	t_list		*elem;
	t_object	*obj;

	ft_lstsort(&game->objects, object_comparator);
	elem = game->objects;
	int fade = 0;
	while (elem)
	{
		obj = (t_object *) elem->content;
		obj->fade = fade % 2;
		draw_object(game, obj);
		fade++;
		elem = elem->next;
	}
}