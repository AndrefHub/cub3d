#include "../inc/cub3d.h"

void	error_exit(t_game *game, int return_value, char *message)
{
	if (return_value)
	{
		ft_putendl_fd(message, 2);
	}
	//free(all)
	// (void ) game;
	mlx_do_key_autorepeaton(game->mlx.id);
	exit(return_value);
}

void	start_mlx(t_game *game)
{
	mlx_mouse_hide(game->mlx.id, game->mlx.window);
	mlx_do_key_autorepeatoff(game->mlx.id);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask, key_hook_press, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask, key_hook_release, game);
	mlx_hook(game->mlx.window, ButtonPress, ButtonPressMask, mouse_hook_press, game);
	mlx_hook(game->mlx.window, ButtonRelease, ButtonReleaseMask, mouse_hook_release, game);
	mlx_hook(game->mlx.window, DestroyNotify, StructureNotifyMask, close_hook, game);
	
	cs_play_sound(game->audio.ctx, game->audio.song.def);
	wait_milliseconds(200);
	init_time(game);
	mlx_loop_hook(game->mlx.id, game_loop, game);
}

void	initialize_game(t_game *game)
{
	game->mlx.window = mlx_new_window(game->mlx.id, WIN_WIDTH, WIN_HEIGHT - 54, PROJ_NAME);
	game->grid = game->map->map;

	game->img.mlx_img = mlx_new_image(game->mlx.id, WIN_WIDTH, WIN_HEIGHT);
	if (game->img.mlx_img == NULL)
		error_exit(game, 0, NULL);
	game->img.addr = (int *) mlx_get_data_addr(game->img.mlx_img, &game->img.bpp, &game->img.line_length, &game->img.endian);
	game->img.size = (t_vector) {WIN_WIDTH, WIN_HEIGHT};

	game->map->img.mlx_img = mlx_new_image(game->mlx.id, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	if (game->map->img.mlx_img == NULL)
		error_exit(game, 0, NULL);
	game->map->img.addr = (int *) mlx_get_data_addr(game->map->img.mlx_img, &game->map->img.bpp, &game->map->img.line_length, &game->map->img.endian);
	game->map->img.size = (t_vector) {WIN_WIDTH / 2, WIN_HEIGHT / 2};
	game->map->map_tile_size = ft_min(game->map->img.size.x / game->map->map_size.x, game->map->img.size.y / game->map->map_size.y);

	game->player.pos = (t_fvector) {(float )game->map->player_coords.x * MAP_GRID_SIZE + MAP_GRID_SIZE / 2, (float )(game->map->player_coords.y - 1) * MAP_GRID_SIZE + MAP_GRID_SIZE / 2};
	game->player.angle = game->map->player_orient;
	game->player.delta.x = cosf(game->player.angle) * 5;
	game->player.delta.y = sinf(game->player.angle) * 5;

	game->column = malloc(sizeof(*game->column) * game->img.size.x);
	ft_memset(game->key.k, 0, 512);
	if (game->column == NULL)
		error_exit(game, 0, NULL);

	game->key.mouse = true;

	game->show_map = false;
}

void	import_texture(t_game *game, t_img *img, char *filename)
{
	int	size;

	size = TEXTURE_SIZE;
	if (ft_strlen(filename) < 5)
		error_exit(game, 1, "Invalid texture filename");
	if (ft_strncmp(".xpm", &filename[ft_strlen(filename) - 4], 4) == 0)
		img->mlx_img = mlx_xpm_file_to_image(game->mlx.id, filename, &size, &size);
	else
		error_exit(game, 1, "Invalid texture format");
	if (img->mlx_img == NULL)
		error_exit(game, 1, filename);
	img->addr = (int *) mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_length, &img->endian);
	img->size.x = TEXTURE_SIZE;
	img->size.y = TEXTURE_SIZE;
}

void	initialize_sprites(t_game *game)
{
	t_list	*img_list;
	t_list	*texture_list;
	t_img	*img;
	int		counter;

	counter = -1;
	while (++counter < MAX_WALL_CHARS)
	{
		texture_list = game->map->texture_list[counter];
		img_list = NULL;
		while (texture_list)
		{
			img = malloc(sizeof(*img));
			import_texture(game, img, texture_list->content);
			ft_lstadd_back(&img_list, ft_lstnew(img));
			texture_list = texture_list->next;
		}
		if (img_list)
			ft_lstlast(img_list)->next = img_list;
		game->map->img_list[counter] = img_list;
		if (img_list)
			game->textures[counter] = *(t_img *)game->map->img_list[counter]->content;
	}
}

void	init_sound(t_game *game)
{
	game->audio.ctx = cs_make_context(0, 44100, 4096, 4, NULL);
	cs_spawn_mix_thread(game->audio.ctx);
	cs_thread_sleep_delay(game->audio.ctx, 5);

	game->audio.song.file = cs_load_wav("assets/sus_sped_up.wav");
	if (game->audio.song.file.channels[0])
	{
		game->audio.song.def = cs_make_def(&game->audio.song.file);
		game->audio.song.def.looped = 1;
	}
	game->audio.bonk.file = cs_load_wav("assets/bonk.wav");
	game->audio.bonk.def = cs_make_def(&game->audio.bonk.file);
	game->audio.bonk.def.volume_left = 1.;
	game->audio.bonk.def.volume_right = 1.;
	// cs_insert_sound(game->sound.ctx, &s0);
}

int	game(t_map *map)
{
	t_game	game;

	game.map = map;
	game.mlx.id = mlx_init();
	if (!game.mlx.id)
		error_exit(&game, 0, NULL);
	init_sound(&game);
	initialize_game(&game);
	initialize_sprites(&game);
	start_mlx(&game);
	mlx_loop(game.mlx.id);
	return (1);
}