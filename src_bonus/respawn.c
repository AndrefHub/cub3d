/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   respawn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:36 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:50:39 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	reset_enemy_position(void *enemy)
{
	t_enemy	*en;

	en = enemy;
	en->object->pos = en->starting_pos;
	ft_lstclear(&en->path, free);
	en->path = NULL;
}

void	reset_positions(t_game *game)
{
	t_list	*enemies;

	game->player.pos = game->player.starting_pos;
	enemies = game->map->enemies;
	ft_lstiter(enemies, reset_enemy_position);
}

int	player_respawn(t_game *game, int *i, t_ull *time)
{
	if (game->hud.lives.value_numeric > 0 && !edibles_eaten(game))
	{
		game->player.health = MAX_HEALTH;
		--game->hud.lives.value_numeric;
		reset_positions(game);
		*time = 0;
		*i = 0;
		change_all_enemies_cry_paused(game, 0);
		set_game_input_mode(game, GAME_MODE);
		return (1);
	}
	return (0);
}
