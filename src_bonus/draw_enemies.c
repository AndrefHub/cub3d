#include "../inc_bonus/cub3d_bonus.h"

int	object_comparator(t_object *obj1, t_object *obj2)
{
	return (obj1->distance < obj2->distance);
}

void	calculate_object_params(t_game *game, t_object *object)
{
	const t_fvector	delta = (t_fvector) {object->pos.x - game->player.pos.x,
									  object->pos.y - game->player.pos.y};
	float angle_to_player;

	angle_to_player = atan2f(delta.y, delta.x) - game->player.angle;
	if (angle_to_player < -PI)
		angle_to_player += 2 * PI;
	object->size.y = (int) (game->col_scale / (cos(angle_to_player) * object->distance));
	object->size.x = object->size.y;
	object->start.x = (game->img.size.x / 2) + tanf(angle_to_player) * game->col_scale - object->size.x / 2;
	object->start.y = (game->img.size.y / 2) - object->size.y / 2 - game->z_offset;
	object->end.x = object->start.x + object->size.x;
	object->end.y = object->start.y + object->size.y;
	object->render_step = (t_fvector)
			{(float) object->sprite->size.x / object->size.x,
			 (float) object->sprite->size.y / object->size.y};
}

void	draw_object_scaled(t_game *game, t_object *object)
{
	const t_vector	draw_start = (t_vector) {ft_max(0, object->start.x),
											   ft_max(0, object->start.y)};
	const t_vector	draw_end = (t_vector) {ft_min(game->img.size.x, object->end.x),
											   ft_min(game->img.size.x, object->end.y)};
	t_fvector		src;
	int				texture_pix;
	t_vector		cur;

	cur = (t_vector) {draw_start.x,draw_start.y};
	src.x = fmaxf(0.f, -object->start.x * object->render_step.x);
	if (object->distance < MAX_RENDER_DISTANCE)
		while (cur.x < draw_end.x)
		{
			cur.y = draw_start.y;
			src.y = fmaxf(0.f, -object->start.y * object->render_step.y);
			if (game->column[cur.x].distance >= object->distance)
				while (cur.y < draw_end.y)
				{
					texture_pix = object->sprite->addr[(unsigned)
							((int) src.y * object->sprite->size.x + src.x)];
					if (texture_pix >> 24 == 0x00)
						put_pixel(&game->img, cur, texture_pix);
					src.y += object->render_step.y;
					cur.y++;
				}
			src.x += object->render_step.x;
			cur.x++;
		}
}

void	update_distance(t_game *game)
{
	t_list		*elem;
	t_object	*object;

	elem = game->objects;
	while (elem)
	{
		object = elem->content;
		object->distance = fvector_distance(game->player.pos, object->pos);
		elem = elem->next;
	}
}

void	draw_game_objects(t_game *game)
{
	t_list		*elem;
	t_object	*obj;

	update_distance(game);
	ft_lstsort(&game->objects, object_comparator);
	elem = game->objects;
	int fade = 0;
	while (elem)
	{
		obj = (t_object *) elem->content;
		obj->fade = fade % 2;
		calculate_object_params(game, obj);
		if (obj->start.x < game->img.size.x && obj->start.y < game->img.size.y
			&& obj->end.x > 0 && obj->end.y > 0)
			draw_object_scaled(game, obj);
		fade++;
		elem = elem->next;
	}
}