/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:44 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 14:48:46 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	init_input_and_scene_funcs(t_game *game)
{
	game->input_funcs[START_MODE]			= start_input_mode;
	game->input_funcs[GAME_MODE] 			= game_input_mode;
	game->input_funcs[LEADERBOARD_MODE] 	= username_input_mode;
	game->input_funcs[WIN_SCREEN_MODE] 		= win_screen_mode;
	game->input_funcs[PAUSE_MODE] 			= pause_mode;
	game->input_funcs[CONTROLS_MENU_MODE] 	= controls_mode;
	game->scene_funcs[START_MODE] 			= (void *)start_game_scene;
	game->scene_funcs[GAME_MODE] 			= (void *)pac_game_scene;
	game->scene_funcs[LEADERBOARD_MODE] 	= (void *)leaderboard_game_scene;
	game->scene_funcs[WIN_SCREEN_MODE] 		= (void *)win_game_scene;
	game->scene_funcs[PAUSE_MODE] 			= (void *)pause_game_scene;
	game->scene_funcs[CONTROLS_MENU_MODE] 	= (void *)controls_game_scene;
}

void	clear_font_outline(t_game *game)
{
	int		counter;
	int		imagecounter;
	t_img	*img;

	counter = -1;
	while (++counter < MAX_FONT_CHARS)
	{
		if (game->map->font[counter].img)
		{
			img = ((t_img *)game->map->font[counter].img->content);
			imagecounter = -1;
			while (++imagecounter < img->size.x * img->size.y)
			{
				((t_rgb *)img->addr + imagecounter)->r = 0xFF;
				((t_rgb *)img->addr + imagecounter)->g = 0xFF;
				((t_rgb *)img->addr + imagecounter)->b = 0xFF;
			}
		}
	}
}

void	play_sounds(t_game *game)
{
	t_list	*list;
	t_enemy	*enemy;

	list = game->map->enemies;
	while (list)
	{
		enemy = list->content;
		enemy->sound.def.volume_left = 0.01;
		enemy->sound.def.volume_right = 0.01;
		enemy->sound.play = cs_play_sound(game->audio.ctx, enemy->sound.def);
		if (enemy->sound.play)
			enemy->sound.play->paused = 1;
		list = list->next;
	}
}

void	start_game(t_game *game)
{
	init_time(game);
	game->audio.sounds[INTRO_SOUND].play
		= cs_play_sound(game->audio.ctx, game->audio.sounds[INTRO_SOUND].def);
	game->audio.sounds[INTRO_SOUND].play->looped = 1;
	mlx_loop(game->mlx.id);
}

int	init_game(t_map *map)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	game.map = map;
	init_input_and_scene_funcs(&game);
	game.scene.parameter = &game;
	game.input_mode = START_MODE;
	game.scene.scene_func = game.scene_funcs[game.input_mode];
	game.mlx.id = mlx_init();
	if (!game.mlx.id)
		error_exit(&game, 1, "Game initialization error: MLX initialization");
	initialize_start_game_variables(&game);
	init_main_game_sound(&game.audio);
	set_game_events_sounds(&game.audio, map->sounds);
	initialize_game_data(&game);
	start_game(&game);
	return (1);
}
