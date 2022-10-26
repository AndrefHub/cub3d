#include "../inc_bonus/cub3d_bonus.h"

int	continue_button_func(void *__game, t_button *button)
{
	resume_game(__game);
	(void)button;
	return (0);
}

int	start_button_func(void *__game, t_button *button)
{
	resume_game(__game);
	change_button_to_pause_mode(__game);
	(void)button;
	return (0);
}

int	controls_button_func(void *__game, t_button *button)
{
	t_game	*game;

	game = __game;
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
