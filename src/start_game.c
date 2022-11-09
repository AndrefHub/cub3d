/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:36 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:47:37 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	start_game(t_game *game)
{
	mlx_loop(game->mlx.id);
}

int	init_game(t_map *map)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	game.map = map;
	game.scene.scene_func = (void *)pac_game_scene;
	game.scene.parameter = &game;
	game.mlx.id = mlx_init();
	if (!game.mlx.id)
		error_exit(&game, 1, "Game initialization error: MLX initialization");
	initialize_start_game_variables(&game);
	initialize_game_data(&game);
	start_game(&game);
	return (1);
}
