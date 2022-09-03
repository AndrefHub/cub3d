#include "../inc/cub3d.h"

t_ull	get_time(void)
{
	struct timeval	time;
	t_ull			milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

void	init_time(t_game *game)
{
	game->time.startup = get_time();
	game->time.last = game->time.startup;
}