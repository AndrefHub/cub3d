#include "../inc_bonus/cub3d_bonus.h"

void	draw_ceil_textured(t_game *game)
{
//	int y;
//
//	y = 0;
//	while (y < game->img.size.y)
//	{
//		t_fvector ray_dir0;
//		t_fvector ray_dir1;
//		ray_dir0.x =
//		y++;
//	}
	(void ) game;
}

void	draw_floor_textured(t_game *game)
{
	int y;
	t_fvector	ray_dir0 = (t_fvector) {(float) game->player.angle
										 + atanf(game->fov * (- (float) game->img.size.x / 2)), 0.f};
	t_fvector	ray_dir1 = (t_fvector) {(float) game->player.angle
										 + atanf(game->fov * (game->img.size.x - (float) game->img.size.x / 2)), 0.f};

	y = 0;
	while (y < game->img.size.y)
	{
		int 		p = y - game->img.size.y / 2;
		float		pos_z = 0.5f * game->img.size.y;
		float		row_distance = pos_z / p;
		float		floor_step_x = row_distance * (ray_dir1.x - ray_dir0.x) / game->img.size.x;
		float		floor_step_y = row_distance * (ray_dir1.y - ray_dir0.y) / game->img.size.y;
		t_fvector	floor = (t_fvector) {game->player.pos.x + row_distance * ray_dir0.x,
										  game->player.pos.y + row_distance * ray_dir0.y};
		int x = 0;
		while (x < game->img.size.x)
		{
			t_vector	cell = (t_vector) {(int) floor.x, (int) floor.y};
			t_vector	tex = (t_vector) {(int) (TEXTURE_SIZE * (floor.x - cell.x)) % TEXTURE_SIZE,
										  (int) (TEXTURE_SIZE * (floor.y - cell.y)) % TEXTURE_SIZE};
			put_pixel(&game->img, (t_vector) {x, y}, game->textures[1].addr[(tex.y * TEXTURE_SIZE * tex.x) % (TEXTURE_SIZE * TEXTURE_SIZE)]);
			put_pixel(&game->img, (t_vector) {x, game->img.size.y - y - 1}, game->textures[1].addr[(tex.y * TEXTURE_SIZE * tex.x) % (TEXTURE_SIZE * TEXTURE_SIZE)]);
			floor.x += floor_step_x;
			floor.y += floor_step_y;
			x++;
		}
		y++;
	}
}