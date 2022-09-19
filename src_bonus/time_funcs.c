#include "../inc_bonus/cub3d_bonus.h"

t_ull	get_time(void)
{
	struct timespec	time;
	t_ull			milliseconds;

	clock_gettime(CLOCK_MONOTONIC, &time);
	milliseconds = (time.tv_sec * 1000) + (time.tv_nsec / 1000000);
	return (milliseconds);
}

t_ull	get_time_hp(void)
{
	struct timespec	time;
	t_ull			microseconds;

	clock_gettime(CLOCK_MONOTONIC, &time);
	microseconds = (time.tv_sec * 1000000) + (time.tv_nsec / 1000);
	return (microseconds);
}

void	init_time(t_game *game)
{
	game->time.startup = get_time();
	game->time.last = game->time.startup;
	game->time.fps_time = game->time.startup;
}

void	wait_milliseconds(int milliseconds)
{
	t_ull	curr_time;

	curr_time = get_time();
	while (get_time() < curr_time + milliseconds)
		usleep(500);
}

void	update_time(t_game *game)
{
	static int	frames = 0;
	// t_ull	curr_time;

	// curr_time = get_time();
	// if (curr_time != game->time.last)
	// 	game->frames = 1000 / (curr_time - game->time.last);
	if (++frames == 10)
	{
		game->time.fps = (1000 * frames) / (get_time() - game->time.fps_time);
		game->time.fps_time = get_time();
		frames = 0;
	}
	game->time.last = get_time();
}