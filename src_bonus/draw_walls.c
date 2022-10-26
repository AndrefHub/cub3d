#include "../inc_bonus/cub3d_bonus.h"

void	draw_wall_scaled(t_img *img, const t_img *texture, t_vector v, t_game *game)
{
	const struct s_column	*column = game->column + v.x;
	double					step;
	unsigned int			tex_x;
	double					tex_y;
	int						max_height;

	step = (double)texture->size.y / column->height;
	tex_x = (unsigned int)column->texture_pos % texture->size.x;
	tex_y = fmaxf(0.f, (float)step * ((float)column->height / 2
				- (float)img->size.y / 2 + (float)game->z_offset));
	v.y = ft_max(0, img->size.y / 2 - column->height / 2 - game->z_offset);
	max_height = ft_min(img->size.y, img->size.y / 2 + column->height / 2
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
		game->column[v.x].height = (int)(game->col_scale
				/ game->column[v.x].perp_dist);
		draw_texture_set(game, &game->column[v.x]);
		draw_wall_scaled(&game->img, &game->textures
		[game->column[v.x].texture_id], v, game);
		++v.x;
	}
}
