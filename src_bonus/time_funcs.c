#include "../inc_bonus/cub3d_bonus.h"

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

void	wait_milliseconds(int milliseconds)
{
	t_ull	curr_time;

	curr_time = get_time();
	while (get_time() < curr_time + milliseconds)
		usleep(500);
}
