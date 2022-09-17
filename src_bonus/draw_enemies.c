#include "../inc_bonus/cub3d_bonus.h"

int	object_comparator(t_object *obj1, t_object *obj2)
{
	return (obj1->distance < obj2->distance);
}

void	calculate_object_params(t_game *game, t_object *object)
{
	t_fvector	delta;


	delta = (t_fvector) {object->pos.x - game->player.pos.x, object->pos.y - game->player.pos.y};
	float angle_to_player = atan2f(delta.y, delta.x) - game->player.angle;
	if (angle_to_player < -PI)
		angle_to_player += 2 * PI;
	object->size.y = (int) (ABS_WALL_SIZE / (cos(angle_to_player) * object->distance));
	object->size.x = object->size.y;
	object->start.x = (game->img.size.x / 2) + tanf(angle_to_player) * ABS_WALL_SIZE - object->size.x / 2;
	object->start.y = (game->img.size.y / 2) - object->size.y / 2 - game->z_offset;
	object->end.x = object->start.x + object->size.x;
	object->end.y = object->start.y + object->size.y;
	object->render_step = (t_fvector)
			{(float) object->sprite->size.x / object->size.x,
			 (float) object->sprite->size.y / object->size.y};
}

void	draw_object_scaled(t_game *game, t_object *object)
{
	float		src_x;
	float		src_y;
	int			texture_pix;
	t_vector	cur;
	t_vector	draw_start;

	draw_start.x = ft_max(0, object->start.x);
	draw_start.y = ft_max(0, object->start.y);

	cur = (t_vector) {draw_start.x,draw_start.y};
	src_x = fmaxf(0.f, -object->start.x * object->render_step.x);
	while (cur.x < object->end.x)
	{
		cur.y = draw_start.y;
		src_y = fmaxf(0.f, -object->start.y * object->render_step.y);
		while (cur.y < object->end.y)
		{
			texture_pix = object->sprite->addr[(unsigned ) ((int)src_y * object->sprite->size.x + src_x)];
			if (texture_pix >> 24 == 0x00)
				put_pixel(&game->img, cur, texture_pix);
			src_y += object->render_step.y;
			cur.y++;
		}
		src_x += object->render_step.x;
		cur.x++;
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
		calculate_object_params(game, obj);
		if (obj->start.x < game->img.size.x && obj->start.y < game->img.size.y
			&& obj->end.x > 0 && obj->end.y > 0)
			draw_object_scaled(game, obj);
		fade++;
		elem = elem->next;
	}
}