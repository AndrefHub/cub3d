#include "../inc_bonus/cub3d_bonus.h"

void	death_message(t_game *game)
{
	const int divisor = 6;
	const int font_size = FONT_SIZE / divisor;

	put_text_to_screen_layout(game, &(t_text){"cub3d (c) 2022 kdancy, lsherry",
		(t_vector){0, game->img.size.y}, VBottom | HLeft}, 16);
	put_text_to_screen_layout(game, &(t_text){"YOU DIED!", (t_vector)
		{WIN_WIDTH / 2, WIN_HEIGHT / 2 - font_size / 2}, VCenter | HCenter},
		divisor);
	put_text_to_screen_layout(game, &(t_text){"1234567890", (t_vector)
		{WIN_WIDTH / 2, WIN_HEIGHT / 2 + font_size / 2}, VCenter | HCenter},
		divisor);
}

void	put_username_on_screen(t_game *game)
{
	t_vector	pos;
	const int divisor = 6;
	const int font_size = FONT_SIZE / divisor;

	pos.x = ft_strlen("username:") * font_size;
	pos.y = WIN_HEIGHT / 2 + font_size;
	put_text_to_screen_layout(game, &(t_text){game->username, pos, VTop | HLeft}, divisor);
	pos.x += ft_strlen(game->username) * font_size;
	draw_square_fill(&game->img, pos, font_size, 0x00000000);
}

void	player_death(t_game *game)
{
	static int		i = 0;
	static t_ull	time = 0;
	// t_rgb	color;

	if (!i)
	{
		cs_pause_sound(game->audio.song.play, 1);
		cs_play_sound(game->audio.ctx, game->audio.bonk.def);
	}
	if (i < 50 && get_time() - time > 50)
	{
		time = get_time();
		dim_image(&game->img, game->img.size.x * game->img.size.y, &(t_rgb){0, 0, 0, 0xFF / (50 - i)});
		mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img,
				0, 0);
		++i;
	}
	else if (i == 50)
	{
		game->input_mode = 1;
		death_message(game);
		put_text_to_screen_layout(game, &(t_text){"username:", (t_vector)
			{0, WIN_HEIGHT / 2 + (FONT_SIZE / 6) * 2}, VBottom | HLeft}, 6);
		++i;
	}
	if (i > 50)
	{
		put_username_on_screen(game);
		mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->hud.mlx_img,
				0, 0);
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
		// rgb->r += ((color->r - rgb->r) * color->a) / (1 << 8);
		// rgb->g += ((color->g - rgb->g) * color->a) / (1 << 8);
		// rgb->b += ((color->b - rgb->b) * color->a) / (1 << 8);
	}
}