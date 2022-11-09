#include "../inc_bonus/cub3d_bonus.h"

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
}

void	initialize_textures(t_game *game)
{
	initialize_sprites(game, MAX_OBJECTS,
		(t_texture *)game->map->object, TEXTURE_SIZE);
	initialize_sprites(game, MAX_WALL_CHARS,
		(t_texture *)game->map->walls, TEXTURE_SIZE);
	initialize_sprites(game, 1, &game->map->floor, TEXTURE_SIZE);
	initialize_sprites(game, 1, &game->map->ceiling, TEXTURE_SIZE);
	initialize_wall_textures(game);
}

void	initialize_game_objects(t_game *game)
{
	t_list		*elem;
	t_object	*obj;

	game->objects = game->map->objects;
	elem = game->objects;
	while (elem)
	{
		obj = elem->content;
		obj->sprite = game->map->object[get_string_index
			(OBJECT_CHARS, obj->type)].img->content;
		elem = elem->next;
	}
	game->objects_count = ft_lstsize(game->objects);
	game->enemies_count = ft_lstsize(game->map->enemies);
}

void	set_enemy_sounds(t_game *game)
{
	t_list	*elem;
	t_enemy	*enemy;

	elem = game->map->enemies;
	while (elem)
	{
		enemy = elem->content;
		copy_sound(&enemy->sound, &game->audio.sounds[ENEMY_SOUND]);
		elem = elem->next;
	}
}

void	*initialize_game_data(void *ptr)
{
	t_game	*game;

	game = ptr;
	initialize_player(game);
	initialize_textures(game);
	initialize_game_objects(game);
	set_enemy_sounds(game);
	// clear_font_outline(game);
	game->lb_filename = get_lb_name(game->map->map_file);
	game->leaderboard = get_leaderboard(game->lb_filename);
	game->death_func = end_game_dim;
	return (NULL);
}