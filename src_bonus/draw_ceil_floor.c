#include "../inc_bonus/cub3d_bonus.h"

static void	draw_row_textured(t_game *game, t_img src, t_vector cur, float row_distance)
{
	const t_fvector	ray_dir0 = (t_fvector) {(float) (cosf(game->player.angle) - game->player.plane.x),
											   (sinf(game->player.angle) - game->player.plane.y)};
	const t_fvector	ray_dir1 = (t_fvector) {(float) (cosf(game->player.angle) + game->player.plane.x),
											   (sinf(game->player.angle) + game->player.plane.y)};
	t_fvector		floor_step;
	t_fvector		floor;
	t_vector		tex;

	floor_step.x = row_distance * (ray_dir1.x - ray_dir0.x) / game->img.size.x;
	floor_step.y = row_distance * (ray_dir1.y - ray_dir0.y) / game->img.size.x;
	floor = (t_fvector) {game->player.pos.x + row_distance * ray_dir0.x,
						 game->player.pos.y + row_distance * ray_dir0.y};
	cur.x = 0;
	while (cur.x < game->img.size.x)
	{

		tex = (t_vector) {(int) (TEXTURE_SIZE * fabsf((floor.x - (int) floor.x))),
						  (int) (TEXTURE_SIZE * fabsf((floor.y - (int) floor.y)))};
		floor.x += floor_step.x;
		floor.y += floor_step.y;
		if (MAX_RENDER_DISTANCE >= row_distance)
			game->img.addr[cur.y * game->img.size.x + cur.x] =
				src.addr[(tex.y * TEXTURE_SIZE + tex.x) % (TEXTURE_SIZE * TEXTURE_SIZE)];
		cur.x++;
	}
}

void	draw_ceil_floor_textured(t_game *game)
{
	float			row_distance;
	t_vector		cur;

	cur.y = 0;
	while (cur.y < game->img.size.y)
	{
		row_distance = (0.5f * (float) game->col_scale)
				/ (cur.y - (game->img.size.y / 2 - game->z_offset));
		if (row_distance < 0)
			draw_row_textured(game, *((t_img *)game->map->ceiling.img->content), cur, -row_distance);
		else
			draw_row_textured(game, *((t_img *)game->map->floor.img->content), cur, row_distance);
		cur.y++;
	}
}
