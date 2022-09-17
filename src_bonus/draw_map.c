#include "../inc_bonus/cub3d_bonus.h"

void	draw_enemies_on_map(t_game *game)
{
	t_list		*enemies;
	t_vector	coords;

	enemies = game->map->enemies;
	while (enemies)
	{
		coords = (t_vector) {((t_enemy *)enemies->content)->pos.x
			* game->map->map_tile_size - game->map->map_tile_size / 4,
			((t_enemy *)enemies->content)->pos.y * game->map->map_tile_size
			- game->map->map_tile_size / 4};
		draw_square_fill(&game->map->img, coords, game->map->map_tile_size / 2,
						0x89D1FE);
		enemies = enemies->next;
	}
}

void	draw_player_on_map(t_game *game)
{
	t_vector	player;
	int			i;

	player = (t_vector) {game->player.pos.x
		* game->map->map_tile_size - game->map->map_tile_size / 4,
		game->player.pos.y * game->map->map_tile_size
		- game->map->map_tile_size / 4};
	i = 0;
	while (i < game->img.size.x - 50)
	{
		draw_line(&game->map->img, (t_vector) {player.x +
		game->map->map_tile_size / 4, player.y + game->map->map_tile_size / 4},
			(t_vector) {game->column[i].pos.x *
			game->map->map_tile_size, game->column[i].pos.y
			* game->map->map_tile_size}, RAYS_COLOR);
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

	fill_img_color(&game->map->img, 0xFF000000);
	y = 0;
	while (game->grid[y])
	{
		x = 0;
		while (game->grid[y][x])
		{
			if (is_wall(game->grid[y][x]))
				draw_square_fill(&game->map->img,
								 (t_vector) {x * game->map->map_tile_size, y * game->map->map_tile_size},
								 game->map->map_tile_size, 0xAA000000);
			else
				draw_square_fill(&game->map->img,
								 (t_vector) {x * game->map->map_tile_size, y * game->map->map_tile_size},
								 game->map->map_tile_size, 0xAAFFFFFF);
			x++;
		}
		y++;
	}
	draw_player_on_map(game);
	draw_enemies_on_map(game);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->map->img.mlx_img, 0, 0);
}

void	draw_fps(t_game *game)
{
	char	*output;
	char	*fps;

	output = malloc(8);
	ft_bzero(output, 8);
	fps = ft_itoa(game->fps);
	// put_text_to_screen_layout(game, &(t_text){
	// 	fps, (t_vector){0, 0}, VTop | HLeft
	// 	}, 15
	// );
	put_text_to_screen_layout(game, &(t_text){
		fps, (t_vector){0, 0}, VTop | HLeft
		}, 15
	);
	free(fps);
	// mlx_string_put(game->mlx.id, game->mlx.window, 0, 15, 0x00FFFFFF, 
	// 	(char []){'0' + fps / 100, '0' + fps / 10 % 10, '0' + fps % 10, '\0'});
	// ++s;
//	f += fps;

//	printf("%f %d\n", ((double)f) / s, fps);
}