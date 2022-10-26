#include "../inc_bonus/cub3d_bonus.h"

int	show_button(t_game *game, t_button *button)
{
	draw_rectangle_fill(&game->hud_img, button->pos, button->size,
		*((int *)&button->background_color));
	put_text_to_screen_layout(game->map->font, &game->hud_img,
		&button->text, game->hud.font_size * 1.5);
	return (0);
}

void	reset_selected_buttons(t_button *buttons, int size)
{
	int	counter;

	counter = -1;
	while (++counter < size)
	{
		buttons[counter].selected = 0;
	}
}

void	all_button_mouse_actions(t_game *game, t_button *buttons, int size)
{
	int	c;

	c = -1;
	mouse_get_pos(game->mlx.id, game->mlx.window, &game->key.mpos.x,&game->key.mpos.y);
	while (++c < size)
	{
		if (buttons[c].pos.x <= game->key.mpos.x && game->key.mpos.x < buttons[c].pos.x + buttons[c].size.x &&
			buttons[c].pos.y <= game->key.mpos.y && game->key.mpos.y < buttons[c].pos.y + buttons[c].size.y)
		{
			reset_selected_buttons(buttons, size);
			buttons[c].selected = 1;
			game->pause.index = c;
		}
	}
}

void	all_button_actions(t_game *game, t_button *buttons, int size)
{
	int	counter;

	counter = -1;
	while (++counter < size)
	{
		button_actions(game, buttons + counter);
	}
}

void	print_pause_menu_entries(t_game *game)
{
	const int	font_size = 60;
	
	draw_rectangle_fill(&game->hud_img,
		(t_vector){game->hud_img.size.x / 2 - game->img.size.x / 2, 0},
		(t_vector){game->img.size.x, game->img.size.y}, 0xA0000000);
	put_text_to_screen_layout(game->map->font, &game->hud_img, 
		&(t_text){"PAUSE", (t_vector){game->hud_img.size.x / 2, font_size},
		VCenter | HCenter, 0xE0E0E0}, font_size);
	all_button_mouse_actions(game, game->pause.buttons, PAUSE_ENTRIES);
	all_button_actions(game, game->pause.buttons, PAUSE_ENTRIES);
}