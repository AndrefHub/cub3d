#include "../inc_bonus/cub3d_bonus.h"

void	initialize_mlx_parameters(t_game *game)
{
	mouse_hide(game->mlx.id, game->mlx.window);
	mlx_do_key_autorepeatoff(game->mlx.id);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask, key_hook_press, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask, key_hook_release, game);
	mlx_hook(game->mlx.window, ButtonPress, ButtonPressMask, mouse_hook_press, game);
	mlx_hook(game->mlx.window, ButtonRelease, ButtonReleaseMask, mouse_hook_release, game);
	mlx_hook(game->mlx.window, DestroyNotify, StructureNotifyMask, close_hook, game);
	mlx_loop_hook(game->mlx.id, game_loop, &game->scene);
	mouse_move(game->mlx.id, game->mlx.window, game->mlx.win_size.x / 2, game->mlx.win_size.y / 2);
}

void	initialize_player(t_game *game)
{
	game->player.pos = (t_fvector) {(float )game->map->player_coords.x
		+ 0.5f,
		(float )(game->map->player_coords.y - 1)
		+ 0.5f};
	game->player.starting_pos = game->player.pos;
	game->player.angle = game->map->player_orient;
	game->player.delta.x = cosf(game->player.angle) * 5;
	game->player.delta.y = sinf(game->player.angle) * 5;

	game->player.plane = (t_fvector) {0.0f, 0.66f};
	game->fov = ((game->img.aspect >= FOV) - (game->img.aspect < FOV)) *
			sqrtf(fabsf((float) M_PI_4 * (game->img.aspect - FOV) / 2)) + M_2_PI;
	game->col_step = tanf(game->fov / (game->img.size.x - 1));
	game->col_scale = 1.0f / game->col_step;
	printf("%f, %f\n", game->col_step, game->fov);
	// game->player.health = 1;
	game->player.last_attack_time = 0;
}

#ifdef __APPLE__

static inline void	get_screen_size(void *mlx_ptr, int *size_x, int *size_y)
{
	(void)mlx_ptr;
	mlx_get_screen_size(size_x, size_y);
	// *size_x = 1280;
	// *size_y = 720;
}

#else

static inline void	get_screen_size(void *mlx_ptr, int *size_x, int *size_y)
{
	mlx_get_screen_size(mlx_ptr, size_x, size_y);
}

#endif

void	initialize_game_hud(t_game *game)
{
	if (game->mlx.win_size.x >= 2560 && game->mlx.win_size.y >= 1440)
	{
		import_texture_to_img(game, &game->hud_texture,
			"assets/textures/hud/pac_hud1440p.xpm", 2560, 1360);
		game->hud.font_size = 30; //TODO: set font_size
		game->mlx.game_size = (t_vector) {1840, 1135};
	}
	else if (game->mlx.win_size.x >= 1920 && game->mlx.win_size.y >= 1080)
	{
		import_texture_to_img(game, &game->hud_texture,
			"assets/textures/hud/pac_hud1080p.xpm", 1920, 1000);
		game->hud.font_size = 20;
		game->mlx.game_size = (t_vector) {1380, 830};
	}
	else if (game->mlx.win_size.x >= 1280 && game->mlx.win_size.y >= 720)
	{
		import_texture_to_img(game, &game->hud_texture,
			"assets/textures/hud/pac_hud720p.xpm", 1280, 720);
		game->mlx.game_size = (t_vector) {920, 607};
		game->hud.font_size = 15;
	}
	game->hud_img = initialize_img(&game->hud_img, game->mlx.id,
		game->mlx.win_size.x, game->mlx.win_size.y);
}

void	initialize_game_parameters(t_game *game)
{
	get_screen_size(game->mlx.id, &game->mlx.win_size.x, &game->mlx.win_size.y);
	game->mlx.window = mlx_new_window(game->mlx.id,
		game->mlx.win_size.x, game->mlx.win_size.y, PROJ_NAME);
	initialize_game_hud(game);
	game->key.mouse = true;
	game->show_map = false;
	game->z_offset = 0;
	game->grid = game->map->map;
	game->img = initialize_img(&game->img, game->mlx.id, game->mlx.game_size.x, game->mlx.game_size.y);
	game->hud_img = initialize_img(&game->hud_img, game->mlx.id, game->mlx.win_size.x, game->mlx.win_size.y);
	game->map->img = initialize_img(&game->map->img, game->mlx.id,
		game->mlx.game_size.x / 2, game->mlx.game_size.y / 2);
	game->map->map_tile_size = ft_min(game->map->img.size.x /
		game->map->map_size.x, game->map->img.size.y / game->map->map_size.y);
	game->column = malloc(sizeof(*game->column) * game->img.size.x);
	ft_memset(game->key.k, 0, 512);
	if (game->column == NULL)
		error_exit(game, 0, NULL);
	init_hud(&game->hud);
}

void	clear_font_outline(t_game *game)
{
	int		counter;
	int		imagecounter;
	t_img	*img;

	counter = -1;
	while (++counter < MAX_FONT_CHARS)
	{
		if (game->map->font[counter].img)
		{
			img = ((t_img *)game->map->font[counter].img->content);
			imagecounter = -1;
			while (++imagecounter < img->size.x * img->size.y)
			{
				((t_rgb *)img->addr + imagecounter)->r = 0xFF;
				((t_rgb *)img->addr + imagecounter)->g = 0xFF;
				((t_rgb *)img->addr + imagecounter)->b = 0xFF;
			}
		}
	}
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
		obj->sprite = game->map->object[get_string_index(OBJECT_CHARS, obj->type)].img->content;
		elem = elem->next;
	}
	game->objects_count = ft_lstsize(game->objects) - ft_lstsize(game->map->enemies);
}

void	set_enemy_sounds(t_game *game)
{
	t_list	*elem;
	t_enemy	*enemy;

	elem = game->map->enemies;
	while (elem)
	{
		enemy = elem->content;
		copy_sound(&enemy->sound, &game->audio.enemy);
		elem = elem->next;
	}
}

void	set_input_mode_chars(t_game *game)
{
	game->macos_chars = "ASDFHGZXCV BQWERYT123465=97-80]OU[IP LJ'K;\\,/NM.  ~ ";
	game->player_lb_data = malloc(sizeof(*game->player_lb_data));
	game->player_lb_data->name = malloc(sizeof(*(game->player_lb_data->name)) * 9);
	game->player_lb_data->score = game->hud.score.value;
	ft_bzero(game->player_lb_data->name, 9);
	game->place = malloc(8);
	ft_bzero(game->place, 8);
	game->input_mode = GAME_MODE;
}

void	play_sounds(t_game *game)
{
	t_list	*list;
	t_enemy	*enemy;

	// game->audio.song.play = cs_play_sound(game->audio.ctx, game->audio.song.def);
	list = game->map->enemies;
	while (list)
	{
		enemy = list->content;
		enemy->sound.def.volume_left = 0.01;
		enemy->sound.def.volume_right = 0.01;
		enemy->sound.play = cs_play_sound(game->audio.ctx, enemy->sound.def);
		list = list->next;
	}
}

void	start_game(t_game *game)
{
	init_time(game);
	play_sounds(game);
	wait_milliseconds(500);
	mlx_loop(game->mlx.id);
}

char	*get_lb_name(char *filename)
{
	char	*lb;
	char	*dot;
	char	*res;

	lb = ft_strrchr(filename, '/');
	if (lb)
		++lb;
	else
		lb = filename;
	dot = ft_strrchr(lb, '.');
	res = ft_strndup(lb, dot - lb);
	lb = ft_strjoin(LEADERBOARD_FOLDER, res);
	free(res);
	res = ft_strjoin(lb, ".lb");
	free(lb);
	return (res);
}

int	init_game(t_map *map)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	game.scene.parameter = &game;
	game.scene.scene_func = (void *) pac_game_scene;
	game.map = map;
	game.mlx.id = mlx_init();
	if (!game.mlx.id)
		error_exit(&game, 1, "Game initialization error: MLX initialization");
	init_main_game_sound(&game);
	set_game_events_sounds(&game.audio, map->sounds);
	initialize_game_parameters(&game);
	initialize_player(&game);
	initialize_sprites(&game, MAX_OBJECTS, (t_texture *)game.map->object, TEXTURE_SIZE);
    initialize_sprites(&game, MAX_FONT_CHARS, (t_texture *)game.map->font, FONT_SIZE);
	initialize_sprites(&game, MAX_WALL_CHARS, (t_texture *)game.map->walls, TEXTURE_SIZE);
	initialize_sprites(&game, 1, &game.map->floor, TEXTURE_SIZE);
	initialize_sprites(&game, 1, &game.map->ceiling, TEXTURE_SIZE);
	initialize_wall_textures(&game);
	initialize_game_objects(&game);
	initialize_mlx_parameters(&game);
	set_input_mode_chars(&game);
	set_enemy_sounds(&game);
	clear_font_outline(&game);
	game.lb_filename = get_lb_name(map->map_file);
	game.leaderboard = get_leaderboard(game.lb_filename);
	start_game(&game);
	return (1);
}