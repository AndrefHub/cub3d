W#include "../inc/cub3d.h"

void	initialize_player(t_game *game)
{
	game->player.pos = (t_fvector){(float)game->map->player_coords.x + 0.5f,
		(float)(game->map->player_coords.y - 1) + 0.5f};
	game->player.starting_pos = game->player.pos;
	game->player.angle = game->map->player_orient;
	game->player.delta.x = cosf(game->player.angle) * 5;
	game->player.delta.y = sinf(game->player.angle) * 5;
	game->player.vector.x = cosf(game->player.angle);
	game->player.vector.y = sinf(game->player.angle);
	game->fov = M_PI / 1.3f;
	game->col_step = tanf(game->fov / (game->img.size.x - 1));
	game->col_scale = 1.0f / game->col_step;
	game->player.plane = (t_fvector){0.0f,
		(114 * atanf(game->col_step * (game->img.size.x / 2)) / 100)};
	game->player.health = 1;
	game->player.last_attack_time = 0;
}

void	initialize_textures(t_game *game)
{
	// initialize_sprites(game, MAX_OBJECTS,
	// 	(t_texture *)game->map->object, TEXTURE_SIZE);
	for (int i = 0; i < MAX_WALL_CHARS; ++i)
		printf("%s\n", game->map->walls[i].texture);
	initialize_sprites(game, MAX_WALL_CHARS,
		(t_texture *)game->map->walls, TEXTURE_SIZE);
	// initialize_sprites(game, 1, &game->map->floor, TEXTURE_SIZE);
	// initialize_sprites(game, 1, &game->map->ceiling, TEXTURE_SIZE);
	initialize_wall_textures(game);
}

void	*initialize_game_data(void *ptr)
{
	t_game	*game;

	game = ptr;
	initialize_player(game);
	initialize_textures(game);
	return (NULL);
}
