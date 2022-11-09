/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game_title_screen.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:53 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 19:06:42 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	initialize_game_hud(t_game *game)
{
	if (game->mlx.win_size.x >= 2560 && game->mlx.win_size.y >= 1440)
	{
		import_texture_to_img(game, &game->hud_texture,
			"assets/textures/hud/pac_hud1440p.xpm", (t_vector){2560, 1360});
		game->hud.font_size = 40;
		game->mlx.game_size = (t_vector){1840, 1135};
	}
	else if (game->mlx.win_size.x >= 1920 && game->mlx.win_size.y >= 1080)
	{
		import_texture_to_img(game, &game->hud_texture,
			"assets/textures/hud/pac_hud1080p.xpm", (t_vector){1920, 1000});
		game->hud.font_size = 30;
		game->mlx.game_size = (t_vector){1380, 830};
	}
	else if (game->mlx.win_size.x >= 1280 && game->mlx.win_size.y >= 720)
	{
		import_texture_to_img(game, &game->hud_texture,
			"assets/textures/hud/pac_hud720p.xpm", (t_vector){1280, 720});
		game->mlx.game_size = (t_vector){920, 607};
		game->hud.font_size = 20;
	}
	game->hud_img = initialize_img(&game->hud_img, game->mlx.id,
			game->mlx.win_size.x, game->mlx.win_size.y);
}

void	initialize_game_parameters(t_game *game)
{
	get_screen_size(game->mlx.id, &game->mlx.win_size.x, &game->mlx.win_size.y);
	game->mlx.window = mlx_new_window(game->mlx.id,
			game->mlx.win_size.x, game->mlx.win_size.y, PROJ_NAME);
	initialize_game_hud(game);
	game->key.mouse = true;
	game->show_map = false;
	game->z_offset = 0;
	game->grid = game->map->map;
	game->img = initialize_img(&game->img, game->mlx.id, game->mlx.game_size.x,
			game->mlx.game_size.y);
	game->hud_img = initialize_img(&game->hud_img, game->mlx.id,
			game->mlx.win_size.x, game->mlx.win_size.y);
	game->map->img = initialize_img(&game->map->img, game->mlx.id,
			game->mlx.game_size.x / 2, game->mlx.game_size.y / 2);
	game->map->map_tile_size = ft_min
		(game->map->img.size.x / game->map->map_size.x,
			game->map->img.size.y / game->map->map_size.y);
	game->col = malloc(sizeof(*game->col) * game->img.size.x);
	ft_memset(game->key.k, 0, 512);
	if (game->col == NULL)
		error_exit(game, 0, NULL);
	init_hud(&game->hud);
	init_buttons(game);
}

void	initialize_mlx_parameters(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx.id);
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask,
		key_hook_press, game);
	mlx_hook(game->mlx.window, KeyRelease, KeyReleaseMask,
		key_hook_release, game);
	mlx_hook(game->mlx.window, ButtonPress, ButtonPressMask,
		mouse_hook_press, game);
	mlx_hook(game->mlx.window, ButtonRelease, ButtonReleaseMask,
		mouse_hook_release, game);
	mlx_hook(game->mlx.window, DestroyNotify, StructureNotifyMask,
		close_hook, game);
	mlx_loop_hook(game->mlx.id, game_loop, &game->scene);
	mouse_move(game->mlx.id, game->mlx.window, game->mlx.win_size.x / 2,
		game->mlx.win_size.y / 2);
}

void	set_input_mode_chars(t_game *game)
{
	game->macos_chars = "ASDFHGZXCV BQWERYT123465=97-80]OU[IP LJ'K;\\,/NM.  ~ ";
	game->player_lb_data = malloc(sizeof(*game->player_lb_data));
	game->player_lb_data->name = malloc(
			sizeof(*game->player_lb_data->name) * 9);
	game->player_lb_data->score = game->hud.score.value;
	ft_bzero(game->player_lb_data->name, 9);
	game->place = malloc(8);
	ft_bzero(game->place, 8);
}

void	initialize_start_game_variables(t_game *game)
{
	import_texture_to_img(game, &game->pacman_logo,
		"assets/textures/pacman_logo.xpm", (t_vector){1280, 384});
	initialize_sprites(game, MAX_FONT_CHARS,
		(t_texture *)game->map->font, FONT_SIZE);
	initialize_game_parameters(game);
	initialize_mlx_parameters(game);
	set_input_mode_chars(game);
}
