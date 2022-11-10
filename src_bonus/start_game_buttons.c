/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game_buttons.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:49 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:59:11 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	init_default_button(t_button *button, int size, char *text)
{
	button->size.y = size * 1.8f;
	button->size.x = size * 12;
	button->background_color = 0x0;
	button->text = (t_text){text, (t_vector){0, 0},
		VCenter | HCenter, 0xFFFFFF};
	button->draw_button = (void *)show_button;
	button->on_selected = selected_arrow_button_func;
	button->on_pressed = selected_button_func;
	button->on_released = default_button_func;
}

void	init_buttons(t_game *game)
{
	const int	font_size = game->hud.font_size * 1.5;
	int			counter;

	init_default_button(game->pause.buttons, font_size, "start");
	init_default_button(game->pause.buttons + 1, font_size, "controls");
	init_default_button(game->pause.buttons + 2, font_size, "exit");
	counter = -1;
	while (++counter < PAUSE_ENTRIES)
	{
		game->pause.buttons[counter].text.pos.x = game->hud_img.size.x * 0.3f;
		game->pause.buttons[counter].text.pos.y = (game->hud_img.size.y * 0.4f)
			+ counter * game->pause.buttons[counter].size.y;
		game->pause.buttons[counter].pos.x = game->pause.buttons[counter]
			.text.pos.x - game->pause.buttons[counter].size.x / 2;
		game->pause.buttons[counter].pos.y = game->pause.buttons[counter]
			.text.pos.y - font_size;
	}
	game->pause.buttons[0].on_released = start_button_func;
	game->pause.buttons[1].on_released = controls_button_func;
	game->pause.buttons[2].on_released = exit_button_func;
	game->pause.buttons[game->pause.index].selected = 1;
}

void	change_button_to_pause_mode(t_game *game)
{
	const int	font_size = game->hud.font_size * 1.5;
	int			counter;

	game->pause.buttons[0].text.text = "continue";
	game->pause.buttons[0].on_released = continue_button_func;
	counter = -1;
	while (++counter < PAUSE_ENTRIES)
	{
		game->pause.buttons[counter].on_selected = selected_button_func;
		game->pause.buttons[counter].background_color = AIM_COLOR;
		game->pause.buttons[counter].text.pos.x = game->hud_img.size.x / 2;
		game->pause.buttons[counter].text.pos.y = font_size * (counter + 2) * 3;
		game->pause.buttons[counter].pos.x = game->hud_img.size.x / 2
			- game->pause.buttons[counter].size.x / 2;
		game->pause.buttons[counter].pos.y = game->pause.buttons
		[counter].text.pos.y - font_size;
	}
}
