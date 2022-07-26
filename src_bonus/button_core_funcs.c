/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_core_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:27 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 19:12:46 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	button_draw(t_game *game, t_button *button)
{
	if (!button->selected && !button->pressed)
		return (button->draw_button(game, button));
	return (0);
}

int	button_selected(t_game *game, t_button *button)
{
	if (button->selected && !button->pressed)
	{
		if (button->selected == 1)
		{
			play_t_sound(game->audio.ctx,
				&game->audio.sounds[BUTTON_CHANGE_SOUND]);
			button->selected = 2;
		}
		return (button->on_selected(game, button));
	}
	return (0);
}

int	button_pressed(t_game *game, t_button *button)
{
	if (button->pressed)
		return (button->on_pressed(game, button));
	return (0);
}

int	button_released(t_game *game, t_button *button)
{
	if (button->released)
	{
		button->released = 0;
		play_t_sound(game->audio.ctx,
			&game->audio.sounds[BUTTON_PRESS_SOUND]);
		return (button->on_released(game, button));
	}
	return (0);
}

int	button_actions(t_game *game, t_button *button)
{
	button_draw(game, button);
	button_selected(game, button);
	button_pressed(game, button);
	button_released(game, button);
	return (0);
}
