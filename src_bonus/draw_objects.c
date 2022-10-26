#include "../inc_bonus/cub3d_bonus.h"

inline void	calculate_object_params_inner(t_game *game, t_object *obj, t_fvector sprite, float inv_det)
{
	t_fvector	transform;
	int			spritescreenx;

	transform.x = inv_det * (game->player.vector.y * sprite.x
			- game->player.vector.x * sprite.y);
	transform.y = inv_det * (-game->player.plane.y * sprite.x
			+ game->player.plane.x * sprite.y);
	spritescreenx = (game->img.size.x / 2) * (1 + transform.x / transform.y);
	obj->start.y = -obj->size.y / 2 + game->img.size.y / 2 - game->z_offset;
	obj->end.y = obj->size.y / 2 + game->img.size.y / 2 - game->z_offset;
	obj->start.x = -obj->size.x / 2 + spritescreenx;
	obj->end.x = obj->size.x / 2 + spritescreenx;
	obj->render_step = (t_fvector){(float) obj->sprite->size.x
		/ obj->size.x, (float) obj->sprite->size.y / obj->size.y};
	if (transform.y <= 0)
		obj->start.x = 2000;
}

void	calculate_object_params(t_game *game, t_object *obj)
{
	float		angle_to_player;
	t_fvector	sprite;
	float		inv_det;

	angle_to_player = atan2f(obj->pos.y - game->player.pos.y,
			obj->pos.x - game->player.pos.x) - game->player.angle;
	if (angle_to_player < -PI)
		angle_to_player += 2 * PI;
	if (obj->distance > 0.1f)
	{
		obj->size.y = (int)(game->col_scale / (cosf(angle_to_player)
					* obj->distance));
		obj->size.x = obj->size.y;
		sprite = (t_fvector){obj->pos.x - game->player.pos.x,
			obj->pos.y - game->player.pos.y};
		inv_det = 1.0f / (game->player.plane.x * game->player.vector.y
				- game->player.vector.x * game->player.plane.y);
		calculate_object_params_inner(game, obj, sprite, inv_det);
	}
}

inline void	draw_object_scaled_inner_cycle(t_game *game, t_object *obj, t_fvector *src, t_vector *cur)
{
	const t_vector	draw_end = (t_vector){ft_min(game->img.size.x, obj->end.x),
		ft_min(game->img.size.y, obj->end.y)};
	unsigned int	texture_pix;

	while (cur->y < draw_end.y)
	{
		texture_pix = obj->sprite->addr[(unsigned)
			((int)src->y * obj->sprite->size.x + src->x)];
		if (src->y > obj->sprite->alpha_start_x[(int) src->x])
			game->img.addr[cur->y * game->img.size.x + cur->x] = texture_pix;
		if (src->y > obj->sprite->alpha_end_x[(int) src->x])
			break ;
		src->y += obj->render_step.y;
		cur->y++;
	}
}

void	draw_object_scaled(t_game *game, t_object *obj)
{
	const t_vector	draw_start = (t_vector){ft_max(0, obj->start.x),
		ft_max(0, obj->start.y)};
	const t_vector	draw_end = (t_vector){ft_min(game->img.size.x, obj->end.x),
		ft_min(game->img.size.y, obj->end.y)};
	t_fvector		src;
	t_vector		cur;

	cur = (t_vector){draw_start.x, draw_start.y};
	src.x = fmaxf(0.f, -obj->start.x * obj->render_step.x);
	if (obj->distance < MAX_RENDER_DISTANCE)
	{
		while (cur.x < draw_end.x)
		{
			if (obj->sprite->alpha_start_x[(int)src.x] != INT16_MAX
				&& game->column[cur.x].distance >= obj->distance)
			{
				src.y = fmaxf(0.f, -obj->start.y * obj->render_step.y);
				cur.y = draw_start.y;
				draw_object_scaled_inner_cycle(game, obj, &src, &cur);
			}
			src.x += obj->render_step.x;
			cur.x++;
		}
	}
}

void	draw_game_objects(t_game *game)
{
	t_list		*elem;
	t_object	*obj;
	int			fade;

	fade = 0;
	update_distance(game);
	ft_lstsort(&game->objects, object_comparator);
	elem = game->objects;
	while (elem)
	{
		obj = (t_object *) elem->content;
		obj->fade = fade % 2;
		calculate_object_params(game, obj);
		if (obj->start.x < game->img.size.x && obj->start.y < game->img.size.y)
			draw_object_scaled(game, obj);
		fade++;
		elem = elem->next;
	}
}
