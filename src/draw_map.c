#include "../inc/cub3d.h"

void	cast_rays(t_game *game)
{
	int		i;
	float	ray_angle;

	i = 0;
	while (i < game->img.size.x)
	{
		ray_angle = game->player.angle + atan(0.001 * (i - (float) game->img.size.x / 2));
		get_interception(game, ray_angle, i);
		i++;
	}
}

void	draw_map_grid(t_game *game)
{
	(void) game;
}

void	draw_rays(t_game *game)
{
	int i;

	i = 0;
	while (i < game->img.size.x - 50)
	{
		draw_line(&game->map->img, (t_vector) {game->player.pos.x, game->player.pos.y}, (t_vector) {game->column[i].pos.x, game->column[i].pos.y}, RAYS_COLOR);
		i += 50;
	}
}

void	draw_player_on_map(t_game *game)
{
	draw_square_fill(&game->map->img, (t_vector) {game->player.pos.x
		- MAP_GRID_SIZE / 4, game->player.pos.y - MAP_GRID_SIZE / 4},
		MAP_GRID_SIZE / 2, PL_MAP_COLOR);
	draw_line(&game->map->img, (t_vector) {game->player.pos.x,
		game->player.pos.y},(t_vector) {game->player.pos.x
		+ cos(game->player.angle) * 20, game->player.pos.y +
		sin(game->player.angle) * 20}, PL_MAP_COLOR);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	img_clear_rgb(&game->map->img, 0xFF000000);
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
	draw_rays(game);
	draw_player_on_map(game);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->map->img.mlx_img, 0, 0);

//	draw_rays(game);
}