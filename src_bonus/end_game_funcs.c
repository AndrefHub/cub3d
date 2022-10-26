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

void	print_leaderboard_entries(t_game *game)
{
	const int	font_size = game->hud.font_size;
	int			counter;
	t_list		*lb;
	t_lb_entry	*entry;

	counter = 0;
	lb = game->leaderboard;
	while (lb && ++counter <= 10)
	{
		entry = lb->content;
		put_text_to_screen_layout(game->map->font, &game->img, set_rank_color
			(&(t_text){get_rank_str(game->place, counter), (t_vector)
			{game->img.size.x / 8, font_size + counter * font_size * 1.5},
				VTop | HCenter, 0xEFEFEF}, counter), font_size);
		put_text_to_screen_layout(game->map->font, &game->img, &(t_text)
		{entry->name, (t_vector){game->img.size.x / 2, font_size + counter
			* font_size * 1.5}, VTop | HCenter, 0xEFEFEF}, font_size);
		put_text_to_screen_layout(game->map->font, &game->img, &(t_text)
		{entry->score, (t_vector){7 * (game->img.size.x / 8), font_size
			+ counter * font_size * 1.5}, VTop | HCenter, 0xEFEFEF}, font_size);
		lb = lb->next;
	}
}

void	leaderboard_message(t_game *game)
{
	const int	font_size = game->hud.font_size;

	put_text_to_screen_layout(game->map->font, &game->img, &(t_text){"rank",
		(t_vector){game->img.size.x / 8, 3 * font_size / 4}, VTop | HCenter,
		0xEFEFEF}, font_size);
	put_text_to_screen_layout(game->map->font, &game->img, &(t_text){"name",
		(t_vector){game->img.size.x / 2, 3 * font_size / 4}, VTop | HCenter,
		0xEFEFEF}, font_size);
	put_text_to_screen_layout(game->map->font, &game->img, &(t_text){"score",
		(t_vector){7 * (game->img.size.x / 8), 3 * font_size / 4},
		VTop | HCenter, 0xEFEFEF}, font_size);
	print_leaderboard_entries(game);
	put_text_to_screen_layout(game->map->font, &game->img, &(t_text)
	{"cub3d (c) 2022 kdancy, lsherry", (t_vector){0, game->img.size.y},
		VBottom | HLeft, 0xBFBFBF}, font_size / 2);
}

void	win_message(t_game *game, char *message, int color)
{
	const int	font_size = game->hud.font_size * 2;

	put_text_to_screen_layout(game->map->font, &game->img, &(t_text){message,
		(t_vector){game->img.size.x / 2, game->img.size.y / 2},
		VCenter | HCenter, color}, font_size);
	put_text_to_screen_layout(game->map->font, &game->img, &(t_text){
		"press enter to continue", (t_vector)
	{game->img.size.x / 2, 5 * game->img.size.y / 8},
		VCenter | HCenter, 0xB0B0B0}, 30);
}
