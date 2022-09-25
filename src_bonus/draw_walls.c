#include "../inc_bonus/cub3d_bonus.h"

//void	draw_floor_textured(t_game *game, t_vector cur);

void	draw_wall_scaled(t_img *img, const t_img *texture,
	const struct s_column *column, int x, t_game * game)
{
	double	step = (double ) texture->size.y / column->height;
	unsigned	tex_x = (unsigned ) column->texture_pos % texture->size.x;
	int				y;
	double			tex_y;
	int 			max_height;

	tex_y = fmaxf(0.f, (float) step * ((float) column->height / 2 - (float) img->size.y / 2 + (float) game->z_offset));
	y = ft_max(0,img->size.y / 2 - column->height / 2 - game->z_offset);
	max_height = ft_min(img->size.y, img->size.y / 2 + column->height / 2 - game->z_offset);
	while (y < max_height)
	{
		put_pixel(img, (t_vector) {x, y}, texture->addr[(unsigned )tex_y * texture->size.x + tex_x]);
		tex_y += step;
		y++;
	}
}

void	draw_walls(t_game *game)
{
	int				x;
//	unsigned int	texture_id;

	x = 0;
	while (x < game->img.size.x)
	{
		game->column[x].height = (int) (game->col_scale / game->column[x].perp_dist);
		draw_texture_set(game, &game->column[x]);
//		texture_id = ft_strchr(CARDINAL_POINTS, game->column[x].dir) - CARDINAL_POINTS;
//		ft_putnbr_fd(texture_id, 1);
		draw_wall_scaled(&game->img, &game->textures[game->column[x].texture_id],
						 &game->column[x], x, game);
		x++;
	}
}