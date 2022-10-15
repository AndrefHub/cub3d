#include "../inc_bonus/cub3d_bonus.h"

char	*get_rank_str(char *str, int rank)
{
	char	*suffix;

	ft_bzero(str, ft_strlen(str));
	ft_put_itoa(str, rank);
	if (rank % 10 == 1)
		suffix = "st";
	else if (rank % 10 == 2)
		suffix = "nd";
	else if (rank % 10 == 3)
	 	suffix = "rd";
	else
	 	suffix = "th";
	ft_strlcat(str + ft_strlen(str), suffix, ft_strlen(suffix) + 1);
	return (str);
}

t_text	*set_rank_color(t_text *text, int rank)
{
	if (rank == 1)
		text->color = 0xFFD700;
	else if (rank == 2)
		text->color = 0xA3BBE4;
	else if (rank == 3)
		text->color = 0xCD7F32;
	return (text);
}

void	leaderboard_message(t_game *game)
{
	const int	font_size = FONT_SIZE / 6;
	int			counter;
	t_list		*lb;
	t_lb_entry	*entry;
	
	counter = 0;
	lb = game->leaderboard;
	put_text_to_screen_layout(game, &game->img, &(t_text){"rank", (t_vector)
	{game->img.size.x / 8, 3 * font_size / 4}, VTop | HCenter, 0xEFEFEF}, font_size);
	put_text_to_screen_layout(game, &game->img, &(t_text){"name", (t_vector)
	{game->img.size.x / 2, 3 * font_size / 4}, VTop | HCenter, 0xEFEFEF}, font_size);
	put_text_to_screen_layout(game, &game->img, &(t_text){"score", (t_vector)
	{7 * (game->img.size.x / 8), 3 * font_size / 4}, VTop | HCenter, 0xEFEFEF}, font_size);
	while (lb && ++counter <= 10)
	{
		entry = lb->content;
		put_text_to_screen_layout(game, &game->img, set_rank_color(&(t_text){get_rank_str(game->place, counter), (t_vector)
		{game->img.size.x / 8, font_size + counter * font_size * 1.5}, VTop | HCenter, 0xEFEFEF}, counter), font_size);
		put_text_to_screen_layout(game, &game->img, &(t_text){entry->name, (t_vector)
		{game->img.size.x / 2, font_size + counter * font_size * 1.5}, VTop | HCenter, 0xEFEFEF}, font_size);
		put_text_to_screen_layout(game, &game->img, &(t_text){entry->score, (t_vector)
		{7 * (game->img.size.x / 8), font_size + counter * font_size * 1.5}, VTop | HCenter, 0xEFEFEF}, font_size);
		lb = lb->next;
	}
	put_text_to_screen_layout(game, &game->img, &(t_text){"cub3d (c) 2022 kdancy, lsherry",
		(t_vector){0, game->img.size.y}, VBottom | HLeft, 0xBFBFBF}, font_size / 2);
}

void	win_message(t_game *game, char *message, int color)
{
	const int	font_size = FONT_SIZE / 3;

	put_text_to_screen_layout(game, &game->img, &(t_text){message, (t_vector)
	{game->img.size.x / 2, game->img.size.y / 2},
		VCenter | HCenter, color}, font_size);
	put_text_to_screen_layout(game, &game->img, &(t_text){
		"press enter to continue", (t_vector)
	{game->img.size.x / 2, 5 * game->img.size.y / 8},
		VCenter | HCenter, 0xB0B0B0}, 30);
	// put_text_to_screen_layout(game, &game->img, &(t_text){game->hud.score.value,
	// 	(t_vector){game->img.size.x / 2, game->img.size.y / 2 + font_size / 2},
	// 	VCenter | HCenter, 0x7FFF7F}, font_size);
	// put_text_to_screen_layout(game, &game->img, &(t_text){"username:", (t_vector)
	// {0, game->img.size.y / 2 + (FONT_SIZE / 6) * 2}, VBottom | HLeft, 0xFF7F7F}, font_size);
}

void	put_username_on_screen(t_game *game)
{
	t_vector	pos;
	const int	divisor = 6;
	const int	font_size = FONT_SIZE / divisor;

	pos.x = ft_strlen("username:") * font_size;
	pos.y = game->img.size.y / 2 + font_size;
	put_text_to_screen_layout(game, &game->img, &(t_text){game->player_lb_data->name, pos,
		VTop | HLeft, 0x727272}, font_size);
	pos.x += ft_strlen(game->player_lb_data->name) * font_size;
	draw_square_fill(&game->img, pos, font_size, 0x00000000);
}

int	edibles_eaten(t_game *game)
{
	return (!game->objects_count);
}

void	change_all_enemies_cry_paused(t_game *game, int paused)
{
	t_list	*enemies;
	t_enemy	*enemy;
	
	enemies = game->map->enemies;
	while (enemies)
	{
		enemy = enemies->content;
		enemy->sound.play->paused = paused;
		enemies = enemies->next;
	}
}

void	pause_game_actions(t_game *game)
{
	// cs_pause_sound(game->audio.song.play, 1);
	cs_play_sound(game->audio.ctx, game->audio.bonk.def);
	game->show_map = 0;
	change_all_enemies_cry_paused(game, 1);
}

void	put_ended_game_image(t_game *game)
{
	fill_img_color(&game->img, 0x0);
	if (game->input_mode == INPUT_MODE)
		leaderboard_message(game);
	else if (game->input_mode == WIN_SCREEN_MODE && edibles_eaten(game))
		win_message(game, "You\'re winner!", 0xFFD700);
	else
		win_message(game, "game over", 0x980000);
	put_frame(game);
}

void	player_death(t_game *game)
{
	static int		i = 0;
	static t_ull	time = 0;

	if (i == 0)
		pause_game_actions(game);
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
			change_all_enemies_cry_paused(game, 0);
			// game->audio.song.play->paused = 0;
			// cs_play_sound(game->audio.ctx, game->audio.song.def);
			return ;
		}
		game->input_mode = WIN_SCREEN_MODE;
		game->player_lb_data->score_num = game->hud.score.value_numeric;
		ft_lst_insert(&game->leaderboard, ft_lstnew(game->player_lb_data), cmp_lb_entry);
		++i;
	}
	if (i > 50)
		put_ended_game_image(game);
}

void	player_win(t_game *game)
{
	static int		i = 0;
	static t_ull	time = 0;

	if (!i)
	{
		// cs_pause_sound(game->audio.song.play, 1);
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
		game->input_mode = WIN_SCREEN_MODE;
		game->player_lb_data->score_num = game->hud.score.value_numeric;
		ft_lst_insert(&game->leaderboard, ft_lstnew(game->player_lb_data), cmp_lb_entry);
		++i;
	}
	if (i > 50)
		put_ended_game_image(game);
}

int	check_aliveness(t_game *game)
{
	return (game->hud.health.value_numeric > 0);
}
