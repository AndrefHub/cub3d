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
//	Идем по всему экрану от 0 до 1920
	while (y < game->img.size.y)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
//		вычисляем направляющие вектора
		ray_dir0 = (t_fvector) {(float) (cosf(game->player.angle) - game->player.plane.x),
								(sinf(game->player.angle) - game->player.plane.y)};
		ray_dir1 = (t_fvector) {(float) (cosf(game->player.angle) + game->player.plane.x),
								(sinf(game->player.angle) + game->player.plane.y)};

		// Current y position compared to the center of the screen (the horizon)
		p = y - game->img.size.y / 2 + game->z_offset;

		// Vertical position of the camera.
		pos_z = 0.5f * (float) game->img.size.y;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		row_distance = pos_z / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		floor_step_x = row_distance * (ray_dir1.x - ray_dir0.x) / game->img.size.x;
		floor_step_y = row_distance * (ray_dir1.y - ray_dir0.y) / game->img.size.x;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		floor = (t_fvector) {game->player.pos.x + row_distance * ray_dir0.x,
							game->player.pos.y + row_distance * ray_dir0.y};

//		printf("%f\n", ray_dir0.x);
		int x = 0;
		while (x < game->img.size.x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			cell = (t_vector) {(int) floor.x, (int) floor.y};

			// get the texture coordinate from the fractional part
			tex = (t_vector) {(int) (TEXTURE_SIZE * fabsf((floor.x - cell.x))),
								(int) (TEXTURE_SIZE * fabsf((floor.y - cell.y)))};
			floor.x += floor_step_x;
			floor.y += floor_step_y;
			if (y > game->img.size.y / 2 - game->z_offset)
				put_pixel(&game->img, (t_vector) {x, y}, game->textures[1].addr[(tex.y * TEXTURE_SIZE + tex.x) % (TEXTURE_SIZE * TEXTURE_SIZE)]);
			else
				put_pixel(&game->img, (t_vector) {game->img.size.x - 1 - x, y}, game->textures[1].addr[(tex.y * TEXTURE_SIZE + tex.x) % (TEXTURE_SIZE * TEXTURE_SIZE)]);
//			put_pixel(&game->img, (t_vector) {x, game->img.size.y - 1 - y}, game->textures[1].addr[(tex.y * TEXTURE_SIZE + tex.x) % (TEXTURE_SIZE * TEXTURE_SIZE)]);
			x++;
		}
		y++;
	}
}

//void	draw_floor_pixel(t_game *game, t_vector cur)
//{
//	t_fvector	real_uv;
//	t_fvector	uv;
//	float		angle;
//
//	real_uv = (t_fvector) {(cur.x - 0.5f * game->img.size.x) / game->img.size.y,
//						   (cur.y - 0.5f * game->img.size.y) / game->img.size.y,};
//	uv = real_uv;
//	angle = uv.x * 0.66f;
//	float	dist = 1.0f / ((fabs(uv.y) + 0.0001) * cosf(uv.x * 0.66f * 1.0f));
//
//	t_fvector floor_uv = (t_fvector) {cosf(angle) * dist, sinf(angle) * dist};
//
//	put_pixel(&game->img, (t_vector) {floor_uv.x, floor_uv.y}, game->textures[1].addr[])
//}
//
//void	draw_floor_textured(t_game *game)
//{
//	int y;
//	int x;
//	y = 0;
//	while (y < game->img.size.y)
//	{
//		x = 0;
//		while (x < game->img.size.x)
//		{
//			draw_floor_pixel(game, (t_vector) {x, y});
//			x++;
//		}
//		y++;
//	}
//}