#include "../inc/cub3d_bonus.h"

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

void	draw_player_on_map(t_game *game)
{
	t_vector	player;
	int			i;

	player = (t_vector) {game->player.pos.x / MAP_GRID_SIZE * game->map->map_tile_size
						 - game->map->map_tile_size / 4, game->player.pos.y / MAP_GRID_SIZE * game->map->map_tile_size - game->map->map_tile_size / 4};
	i = 0;
	while (i < game->img.size.x - 50)
	{
		draw_line(&game->map->img, (t_vector) {player.x + game->map->map_tile_size / 4, player.y + game->map->map_tile_size / 4}, (t_vector) {game->column[i].pos.x / MAP_GRID_SIZE * game->map->map_tile_size, game->column[i].pos.y / MAP_GRID_SIZE * game->map->map_tile_size}, RAYS_COLOR);
		i += 50;
	}
	draw_square_fill(&game->map->img, player, game->map->map_tile_size / 2,
					 PL_MAP_COLOR);
	draw_line(&game->map->img, (t_vector) {player.x + game->map->map_tile_size / 4, player.y + game->map->map_tile_size / 4},(t_vector) {player.x + game->map->map_tile_size / 4
		+ cos(game->player.angle) * game->map->map_tile_size / 2, player.y + game->map->map_tile_size / 4 +
		sin(game->player.angle) * game->map->map_tile_size / 2}, PL_MAP_COLOR);

}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	img_clear_rgb(&game->map->img, 0xAA000000);
	// img_clear_rgb(&game->map->img, 0xFF000000);
	y = 0;
	while (game->grid[y])
	{
		x = 0;
		while (game->grid[y][x])
		{
			if (game->grid[y][x] == '0' || game->grid[y][x] == 'N')
				draw_square_fill(&game->map->img,
								 (t_vector) {x * game->map->map_tile_size, y * game->map->map_tile_size},
								 game->map->map_tile_size, 0xAAFFFFFF);
			else if (is_wall(game->grid[y][x]))
				draw_square_fill(&game->map->img,
								 (t_vector) {x * game->map->map_tile_size, y * game->map->map_tile_size},
								 game->map->map_tile_size, 0xAA000000);
			x++;
		}
		y++;
	}
	draw_player_on_map(game);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->map->img.mlx_img, 0, 0);

//	draw_rays(game);
}