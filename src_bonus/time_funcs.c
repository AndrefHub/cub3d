/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:55 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:50:58 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	game->hud.fps.value_numeric = game->time.startup;
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

	if (++frames == 10)
	{
		game->hud.fps.value_numeric = 9999;
		if (get_time() != game->time.fps_time)
			game->hud.fps.value_numeric = (1000 * frames)
				/ (get_time() - game->time.fps_time);
		if (game->hud.fps.value_numeric > 9999)
			game->hud.fps.value_numeric = 9999;
		game->time.fps_time = get_time();
		frames = 0;
	}
	game->time.last = get_time();
}
