#include "../inc_bonus/cub3d_bonus.h"

void	death_message(t_game *game)
{
	const int	divisor = 6;
	const int	font_size = FONT_SIZE / divisor;

	put_text_to_screen_layout(game, &(t_text){"cub3d (c) 2022 kdancy, lsherry",
		(t_vector){0, game->img.size.y}, VBottom | HLeft}, 16);
	put_text_to_screen_layout(game, &(t_text){"YOU DIED!", (t_vector)
	{WIN_WIDTH / 2, WIN_HEIGHT / 2 - font_size / 2}, VCenter | HCenter},
		font_size);
	put_text_to_screen_layout(game, &(t_text){game->hud.score.title, (t_vector)
	{WIN_WIDTH / 2, WIN_HEIGHT / 2 + font_size / 2}, VCenter | HCenter},
		font_size);
	put_text_to_screen_layout(game, &(t_text){"username:", (t_vector)
	{0, WIN_HEIGHT / 2 + (FONT_SIZE / 6) * 2}, VBottom | HLeft}, font_size);
}

void	put_username_on_screen(t_game *game)
{
	t_vector	pos;
	const int	divisor = 6;
	const int	font_size = FONT_SIZE / divisor;

	pos.x = ft_strlen("username:") * font_size;
	pos.y = WIN_HEIGHT / 2 + font_size;
	put_text_to_screen_layout(game, &(t_text){game->username, pos,
		VTop | HLeft}, font_size);
	pos.x += ft_strlen(game->username) * font_size;
	draw_square_fill(&game->img, pos, font_size, 0x00000000);
}

void	player_death(t_game *game)
{
	static int		i = 0;
	static t_ull	time = 0;

	if (!i)
	{
		cs_pause_sound(game->audio.song.play, 1);
		cs_play_sound(game->audio.ctx, game->audio.bonk.def);
		game->show_map = 0;
	}
	if (i < 50 && get_time() - time > 35)
	{
		time = get_time();
		dim_screen(game, i);
		++i;
	}
	else if (i == 50)
	{
		if (player_respawn(game))
		{
			i = 0;
			time = 0;
			return ;
		}
		game->input_mode = 1;
		death_message(game);
		put_text_to_screen_layout(game, &(t_text){"username:", (t_vector)
		{0, WIN_HEIGHT / 2 + (FONT_SIZE / 6) * 2}, VBottom | HLeft}, 40);
		++i;
	}
	if (i > 50)
	{
		fill_img_color(&game->img, 0x0);
		death_message(game);
		put_username_on_screen(game);
		put_frame(game);
	}
}

int	check_aliveness(t_game *game)
{
	return (game->hud.health.value > 0);
}
