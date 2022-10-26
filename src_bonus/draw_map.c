#include "../inc_bonus/cub3d_bonus.h"

void	draw_objects_on_map(t_game *game)
{
	t_list		*elem;
	t_object	*object;
	t_vector	coords;

	elem = game->objects;
	while (elem)
	{
		object = elem->content;
		coords = (t_vector){object->pos.x * game->map->map_tile_size
			- game->map->map_tile_size / 6, object->pos.y
			* game->map->map_tile_size - game->map->map_tile_size / 6};
		draw_square_fill(&game->map->img, coords,
			game->map->map_tile_size / 3, OBJECTS_MAP_COLOR);
		elem = elem->next;
	}
}

void	draw_enemies_on_map(t_game *game)
{
	t_list		*enemies;
	t_vector	coords;

	enemies = game->map->enemies;
	while (enemies)
	{
		coords = (t_vector){((t_enemy *)enemies->content)->object->pos.x
			* game->map->map_tile_size - game->map->map_tile_size / 4,
			((t_enemy *)enemies->content)->object->pos.y
			* game->map->map_tile_size - game->map->map_tile_size / 4};
		draw_square_fill(&game->map->img, coords, game->map->map_tile_size / 2,
			ENEMIES_MAP_COLOR);
		enemies = enemies->next;
	}
}

void	draw_player_on_map(t_game *game)
{
	t_vector	player;
	int			i;

	player = (t_vector){game->player.pos.x
		* game->map->map_tile_size - game->map->map_tile_size / 4,
		game->player.pos.y * game->map->map_tile_size
		- game->map->map_tile_size / 4};
	i = 0;
	while (i < game->img.size.x - 50)
	{
		draw_line(&game->map->img, (t_vector){player.x
			+ game->map->map_tile_size / 4, player.y
			+ game->map->map_tile_size / 4}, (t_vector){game->column[i].pos.x
			* game->map->map_tile_size, game->column[i].pos.y
			* game->map->map_tile_size}, RAYS_COLOR);
		i += 50;
	}
	draw_square_fill(&game->map->img, player, game->map->map_tile_size / 2,
		PL_MAP_COLOR);
	draw_line(&game->map->img, (t_vector){player.x + game->map->map_tile_size
		/ 4, player.y + game->map->map_tile_size / 4}, (t_vector)
	{player.x + game->map->map_tile_size / 4 + game->player.vector.x
		* game->map->map_tile_size / 2, player.y + game->map->map_tile_size / 4
		+ game->player.vector.y * game->map->map_tile_size / 2}, PL_MAP_COLOR);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	fill_img_color(&game->map->img, TRANSPARENT_COLOR);
	y = 0;
	while (game->grid[y])
	{
		x = 0;
		while (game->grid[y][x])
		{
			if (is_wall(game->grid[y][x]))
				draw_square_fill(&game->map->img, (t_vector){x * game->map
					->map_tile_size, y * game->map->map_tile_size},
					game->map->map_tile_size, MAP_BG_COLOR);
			else
				draw_square_fill(&game->map->img, (t_vector){x * game->map
					->map_tile_size, y * game->map->map_tile_size},
					game->map->map_tile_size, MAP_WALLS_COLOR);
			x++;
		}
		y++;
	}
	draw_player_on_map(game);
	draw_objects_on_map(game);
	draw_enemies_on_map(game);
}
