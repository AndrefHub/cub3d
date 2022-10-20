#include "../inc_bonus/cub3d_bonus.h"

int	default_button_func(void *v, struct s_button *b)
{
	(void)v;
	(void)b;
	return (0);
}

int	button_selected(t_game *game, t_button *button)
{
	if (button->selected && !button->pressed)
		return (button->on_selected(game, button));
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
		return (button->on_released(game, button));
	}
	return (0);
}

int	button_actions(t_game *game, t_button *button)
{
	button_selected(game, button);
	button_pressed(game, button);
	button_released(game, button);
	return (0);
}