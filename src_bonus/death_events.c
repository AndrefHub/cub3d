#include "../inc_bonus/cub3d_bonus.h"

void	death_message(t_game *game)
{
	put_text_to_screen_layout(game, "YOU DIED!", (t_vector)
		{WIN_WIDTH / 2, WIN_HEIGHT / 2 - FONT_SIZE / 2}, VCenter | HCenter);
	put_text_to_screen_layout(game, "1234567890", (t_vector)
		{WIN_WIDTH / 2, WIN_HEIGHT / 2 + FONT_SIZE / 2}, VCenter | HCenter);
}

void	player_death(t_game *game)
{
	static int		it = 0;
	static t_ull	time = 0;
	// t_rgb	color;

	if (!it)
	{
		cs_pause_sound(game->audio.song.play, 1);
		cs_play_sound(game->audio.ctx, game->audio.bonk.def);
	}
	if (it < 50 && get_time() - time > 50)
	{
		time = get_time();
		dim_image(&game->img, game->img.size.x * game->img.size.y, &(t_rgb){0, 0, 0xFF, 0xFF / (50 - it)});
		mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img,
				0, 0);
		++it;
	}
	else if (it == 50)
	{
		game->input_mode = 1;
		death_message(game);
		++it;
	}
	if (it > 50)
	{
		// mlx_clear_window(game->mlx.id, game->mlx.window);
		death_message(game);
		put_text_to_screen_layout(game, "username: ", (t_vector)
			{0, WIN_HEIGHT / 2 + FONT_SIZE * 2}, VBottom | HLeft);
		put_text_to_screen_layout(game, game->username, (t_vector)
			{ft_strlen("username: ") * FONT_SIZE, WIN_HEIGHT / 2 + FONT_SIZE * 2}, VBottom | HLeft);
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