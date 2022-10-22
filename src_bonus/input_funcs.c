#include "../inc_bonus/cub3d_bonus.h"

int	pause_game(t_game *game)
{
	t_list	*lst;

	lst = game->map->enemies;
	while (lst)
	{
		((t_enemy *)lst->content)->sound.play->paused = 1;
		lst = lst->next;
	}
	mouse_show(game->mlx.id, game->mlx.window);
	set_game_input_mode(game, PAUSE_MODE);
	return (0);
}

int	resume_game(t_game *game)
{
	t_list	*lst;

	lst = game->map->enemies;
	while (lst)
	{
		((t_enemy *)lst->content)->sound.play->paused = 0;
		lst = lst->next;
	}
	mouse_hide(game->mlx.id, game->mlx.window);
	set_game_input_mode(game, GAME_MODE);
	mouse_move(game->mlx.id, game->mlx.window, game->mlx.win_size.x / 2, game->mlx.win_size.y / 2);
	return (0);
}

// set_game_input_mode(game, GAME_MODE) (0) //
inline int	game_input_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
		pause_game(game);
	else
	{
		if (key == M_KEY)
		{
			game->show_map = !game->show_map;
			return (0);
		}
		if (key == E_KEY)
			open_door(game);
		game->key.k[(short)(key + CHAR_OFFSET)] = true;
	}
	return (0);
}

// set_game_input_mode(game, LEADERBOARD_MODE) (1) //
inline int	username_input_mode(int key, t_game *game)
{
	if (key == ESC_KEY && ft_strlen(game->player_lb_data->name))
		close_hook(game);
	if (key == BACKSPACE) // Backspace
		game->player_lb_data->name[ft_strlen(game->player_lb_data->name) - 1]
			= '\0';
	else if (key == ENTER) // Enter, to add confirm action
		update_leaderboard_file(game);
	else
		input_char(key, game->player_lb_data->name, game->macos_chars);
	return (0);
}

// set_game_input_mode(game, WIN_SCREEN_MODE) (2) //
inline int	win_screen_mode(int key, t_game *game)
{
	if (key == ENTER)
		set_game_input_mode(game, LEADERBOARD_MODE);
	return (0);
}

// set_game_input_mode(game, PAUSE_MODE) (3) //
inline int	pause_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
	{
		close_hook(game);
	}
	else if (key == DOWN_KEY)
	{
		game->pause.buttons[game->pause.index].selected = 0;
		game->pause.index = (game->pause.index + 1) % PAUSE_ENTRIES;
		game->pause.buttons[game->pause.index].selected = 1;
		printf("%d\n", game->pause.index);
	}
	else if (key == UP_KEY)
	{
		game->pause.buttons[game->pause.index].selected = 0;
		game->pause.index = (game->pause.index + PAUSE_ENTRIES - 1) % PAUSE_ENTRIES;
		game->pause.buttons[game->pause.index].selected = 1;
		printf("%d\n", game->pause.index);
	}
	// else if (key == ENTER)
	// {
	// 	set_game_input_mode(game, GAME_MODE);
	// 	game->scene.scene_func = (void *)pac_game_scene;
	// }
	return (0);
}	

// set_game_input_mode(game, CONTROLS_MODE (4) //
inline int	controls_mode(int key, t_game *game)
{
	if (key == ESC_KEY)
	{
		set_game_input_mode(game, PAUSE_MODE);
		game->scene.scene_func = (void *)pause_game_scene;
	}
	// else if (key == ENTER)
	// {
	// 	set_game_input_mode(game, GAME_MODE);
	// 	game->scene.scene_func = (void *)pac_game_scene;
	// }
	return (0);
}	
