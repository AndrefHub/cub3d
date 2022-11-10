/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:24 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 15:02:13 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	continue_button_func(void *__game, t_button *button)
{
	resume_game(__game);
	(void)button;
	return (0);
}

int	start_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	resume_game(game);
	change_button_to_pause_mode(game);
	game->start_game_time = get_time();
	(void)button;
	return (0);
}

int	controls_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
	game->index_before_controls = game->input_mode;
	set_game_input_mode(game, CONTROLS_MENU_MODE);
	(void)button;
	return (0);
}

int	exit_button_func(void *game, t_button *button)
{
	(void)button;
	error_exit(game, 0, "exit from menu");
	return (0);
}
