#include "../inc/cub3d.h"

void	draw_rays(t_game *game)
{
	int		i;
	float	ray_angle;

	i = 0;
	while (i < game->img.size.x)
	{
		//TODO: set to 0.66 degrees player's camera angel
		ray_angle = game->player.angle + atan(0.001 * (i - (float) game->img.size.x / 2));
		get_interception(game, ray_angle, i);
		i++;
	}
}

void	draw_map_grid(t_game *game)
{
	(void) game;
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	img_clear_rgb(&game->map->img, 0xAA000000);
	y = 0;
	while (game->grid[y])
	{
		x = 0;
		while (game->grid[y][x])
		{
			if (game->grid[y][x] == '0' || game->grid[y][x] == 'N')
				draw_square_fill(&game->map->img,
								 (t_vector) {x * MAP_GRID_SIZE, y * MAP_GRID_SIZE},
								 MAP_GRID_SIZE, 0xAAFFFFFF);
			else if (game->grid[y][x] == '1')
				draw_square_fill(&game->map->img,
								 (t_vector) {x * MAP_GRID_SIZE, y * MAP_GRID_SIZE},
								 MAP_GRID_SIZE, 0xAA000000);
			x++;
		}
		y++;
	}
	draw_square_fill(&game->map->img, (t_vector) {game->player.pos.x - MAP_GRID_SIZE / 4, game->player.pos.y - MAP_GRID_SIZE / 4}, MAP_GRID_SIZE / 2, 0xFF0000);
	draw_line(&game->map->img, (t_vector) {game->player.pos.x, game->player.pos.y},
			  (t_vector) {game->player.pos.x + game->player.delta.x * 5, game->player.pos.y + game->player.delta.y * 5}, 0xFF0000);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->map->img.mlx_img, 0, 0);

//	draw_rays(game);
}