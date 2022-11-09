#include "../inc/cub3d.h"

void	draw_wall_scaled(t_img *img, const t_img *texture, t_vector v, t_game *game)
{
	const struct s_column	*col = game->col + v.x;
	double					step;
	unsigned int			tex_x;
	double					tex_y;
	int						max_height;

	step = (double)texture->size.y / col->height;
	tex_x = (unsigned int)col->texture_pos % texture->size.x;
	tex_y = fmaxf(0.f, (float)step * ((float)col->height / 2
				- (float)img->size.y / 2 + (float)game->z_offset));
	v.y = ft_max(0, img->size.y / 2 - col->height / 2 - game->z_offset);
	max_height = ft_min(img->size.y, img->size.y / 2 + col->height / 2
			- game->z_offset);
	while (v.y < max_height)
	{
		img->addr[v.y * img->size.x + v.x] = texture->addr
		[(unsigned)tex_y * texture->size.x + tex_x];
		tex_y += step;
		++v.y;
	}
}

void	draw_walls(t_game *game)
{
	t_vector	v;

	v.x = 0;
	while (v.x < game->img.size.x)
	{
		game->col[v.x].height = (int)(game->col_scale
				/ game->col[v.x].perp_dist);
		game->col[v.x].texture_id = ft_strchr(CARDINAL_POINTS,
			game->col[v.x].dir) - CARDINAL_POINTS;
		draw_wall_scaled(&game->img, &game->textures
		[game->col[v.x].texture_id], v, game);
		++v.x;
	}
}
