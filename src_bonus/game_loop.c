#include "../inc_bonus/cub3d_bonus.h"

void	draw_hud(t_game *game, t_ull time1, t_ull time2)
{
	mlx_string_put(game->mlx.id, game->mlx.window, 40, 15, 0x00FFFFFF,
				   "tr:");
	mlx_string_put(game->mlx.id, game->mlx.window, 60, 15, 0x00FFFFFF, \
		(char []){'0' + time1 / 1000, '0' + time1 / 100 % 10, '0' + time1 / 10 % 10, '0' + time1 % 10, '\0'});
	mlx_string_put(game->mlx.id, game->mlx.window, 100, 15, 0x00FFFFFF,
				   "td:");
	mlx_string_put(game->mlx.id, game->mlx.window, 120, 15, 0x00FFFFFF, \
		(char []){'0' + time2 / 1000, '0' + time2 / 100 % 10, '0' + time2 / 10 % 10, '0' + time2 % 10, '\0'});
}

void	death_message(t_game *game)
{
	cs_pause_sound(game->audio.song.play, 1);
	put_text_to_screen_centered(game, "YOU DIED!", (t_vector)
		{WIN_WIDTH / 2, WIN_HEIGHT / 2 - FONT_SIZE / 2});
	put_text_to_screen_centered(game, "1234567890", (t_vector)
		{WIN_WIDTH / 2, WIN_HEIGHT / 2 + FONT_SIZE / 2});
}

void	player_death(t_game *game)
{
	static int	it = 0;
	static t_ull	time = 0;
	// t_rgb	color;

	if (!it)
	{
		cs_pause_sound(game->audio.song.play, 1);
		cs_play_sound(game->audio.ctx, game->audio.bonk.def);
	}
	if (get_time() - time > 500 && it < 10)
	{
		time = get_time();
		dim_image(&game->img, game->img.size.x * game->img.size.y, &(t_rgb){0, 0, 0, 0xFF / (10 - it)});
		mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img,
						0, 0);
		++it;
	}
	else if (it == 10)
	{
		death_message(game);
	}
}

int	check_aliveness(t_game *game)
{
	return (game->player.health > 0);
}

void	dim_image(t_img *img, int img_size, t_rgb *color) // works for non-transparent images only (alpha == 0xFF)
{
	int				counter;
	t_rgb			*rgb;

	counter = -1;
	if (color->a == 0xFF)
		while (++counter < img_size)
			img->addr[counter] = *(int *)color;
	while (++counter < img_size)
	{
		rgb = (t_rgb *)(img->addr + counter);
		rgb->r += ((color->r - rgb->r) * color->a) / (1 << 8);
		rgb->g += ((color->g - rgb->g) * color->a) / (1 << 8);
		rgb->b += ((color->b - rgb->b) * color->a) / (1 << 8);
	}
}

int	game_loop(t_game *game)
{
	if (check_aliveness(game))
	{
		player_controll(game);
		enemy_move(game);
		fill_img_color(&game->img, 0x808080);
		fill_ceiling_color(&game->img, game->map->C, game->horizon);
		draw_ceil_textured(game);
		fill_floor_color(&game->img, game->map->F, game->horizon);
	//	draw_player(game);
	//  draw_hud(game);
		t_ull time = get_time();
		cast_rays(game);	
		t_ull time_rays = get_time() - time;
		time = get_time();
		draw_walls(game);
		t_ull time_drawing = get_time() - time;
		printf("*** %llu *** %llu ***\n", time_rays, time_drawing);
		draw_aim(game);

		mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img,
								0, 0);
		if (game->show_map)
			draw_map(game);

		change_textures(game);
	}
	else 
	{
		player_death(game);
	}
	draw_fps(game);
	game->time.last = get_time();
	return (0);
}