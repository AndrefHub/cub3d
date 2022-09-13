#include "../inc_bonus/cub3d_bonus.h"

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
	if (get_time() - time > 50 && it < 50)
	{
		time = get_time();
		dim_image(&game->img, game->img.size.x * game->img.size.y, &(t_rgb){0, 0, 0, 0xFF / (50 - it)});
		mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img,
						0, 0);
		++it;
	}
	else if (it == 50)
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