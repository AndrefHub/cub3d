#include "../inc_bonus/cub3d_bonus.h"

void	draw_ceil_textured(t_game *game)
{
	(void ) game;
}

void	draw_floor_textured(t_game *game)
{
	int y;
	t_fvector	ray_dir0;
	t_fvector	ray_dir1;
	int 		p;
	float		pos_z;
	float		row_distance;
	float		floor_step_x;
	float		floor_step_y;
	t_fvector	floor;
	t_vector	cell;
	t_vector	tex;

	y = 0;
	while (y < game->img.size.y)
	{
		ray_dir0 = (t_fvector) {(float) (cosf(game->player.angle) - game->player.plane.x),
								(sinf(game->player.angle) - game->player.plane.y)};
		ray_dir1 = (t_fvector) {(float) (cosf(game->player.angle) + game->player.plane.x),
								(sinf(game->player.angle) + game->player.plane.y)};

		p = y - (game->img.size.y / 2 - game->z_offset);
		pos_z = 0.5f * (float) game->col_scale;
		row_distance = pos_z / p;
		floor_step_x = row_distance * (ray_dir1.x - ray_dir0.x) / game->img.size.x;
		floor_step_y = row_distance * (ray_dir1.y - ray_dir0.y) / game->img.size.x;
		floor = (t_fvector) {game->player.pos.x + row_distance * ray_dir0.x,
							game->player.pos.y + row_distance * ray_dir0.y};

		int x = 0;
		while (x < game->img.size.x)
		{
			cell = (t_vector) {(int) floor.x, (int) floor.y};

			tex = (t_vector) {(int) (TEXTURE_SIZE * fabsf((floor.x - (float) cell.x))),
								(int) (TEXTURE_SIZE * fabsf((floor.y - (float) cell.y)))};
			floor.x += floor_step_x;
			floor.y += floor_step_y;
			if (row_distance > 0)
			{
				put_pixel(&game->img, (t_vector) {x, y}, game->textures[1].addr[(tex.y * TEXTURE_SIZE + tex.x) % (TEXTURE_SIZE * TEXTURE_SIZE)]);
			}
//			else
//				put_pixel(&game->img, (t_vector) {game->img.size.x - 1 - x, y}, game->textures[1].addr[(tex.y * TEXTURE_SIZE + tex.x) % (TEXTURE_SIZE * TEXTURE_SIZE)]);
			x++;
		}
		y++;
	}
}
