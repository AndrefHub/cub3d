/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:01 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 19:18:36 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	in_bounds_vec(t_vector map_size, t_vector obj)
{
	return (0 < obj.x && obj.x < map_size.x - 1 && 0 < obj.y
		&& obj.y < map_size.y - 1);
}

int	in_bounds(t_vector map_size, int x, int y)
{
	return (0 < x && x < map_size.x - 1 && 0 < y && y < map_size.y - 1);
}

t_fvector	fvector_normalization(t_fvector vec)
{
	float	len;

	len = fvector_distance((t_fvector){0, 0}, vec);
	vec.x /= len;
	vec.y /= len;
	return (vec);
}

t_list	*pathfinding_algo_straight(t_game *game, t_enemy *enemy)
{
	t_vector	en;

	en = (t_vector){enemy->object->pos.x, enemy->object->pos.y};
	if (in_bounds_vec(game->map->map_size, en))
		return (get_first_n_nodes(astar(game, en, (t_vector)
					{game->player.pos.x, game->player.pos.y}), 5));
	return (NULL);
}

t_list	*pathfinding_algo_predict(t_game *game, t_enemy *enemy)
{
	t_vector	en;
	t_fvector	pl;
	int			stopper;

	if (distancef(&enemy->object->pos, &game->player.pos) > 5)
	{
		en = (t_vector){enemy->object->pos.x, enemy->object->pos.y};
		pl = (t_fvector){game->player.pos.x + game->player.vector.x * 5,
			game->player.pos.y + game->player.vector.y * 5};
		stopper = 0;
		while (++stopper < 10
			&& (!in_bounds(game->map->map_size, (int)pl.x, (int)pl.y)
				|| is_wall(game->map->map[(int)pl.y][(int)pl.x])))
		{
			pl.x -= game->player.vector.x * .5f;
			pl.y -= game->player.vector.y * .5f;
		}
		if (in_bounds_vec(game->map->map_size, en))
			return (get_first_n_nodes(astar(game,
						en, (t_vector){pl.x, pl.y}), 5));
	}
	return (pathfinding_algo_straight(game, enemy));
}

t_list	*pathfinding_algo_giga_predict(t_game *game, t_enemy *enemy)
{
	t_vector	en;
	t_fvector	diff;
	t_fvector	pl;
	int			stopper;

	en = (t_vector){enemy->object->pos.x, enemy->object->pos.y};
	diff = (t_fvector){game->player.pos.x + game->player.vector.x * 2,
		game->player.pos.y + game->player.vector.y * 2};
	pl = (t_fvector){game->player.pos.x + diff.x, game->player.pos.y + diff.y};
	diff = fvector_normalization(diff);
	stopper = 0;
	while (++stopper < 50
		&& (!in_bounds(game->map->map_size, (int)pl.x, (int)pl.y)
			|| is_wall(game->map->map[(int)pl.y][(int)pl.x])))
	{
		pl.x -= diff.x * .5f;
		pl.y -= diff.y * .5f;
	}
	if (in_bounds_vec(game->map->map_size, en))
		return (get_first_n_nodes(astar(game,
					en, (t_vector){pl.x, pl.y}), 5));
	return (NULL);
}
