/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:48:47 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:25:24 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	enemy_attack(t_game *game, t_enemy *enemy)
{
	if (enemy->panic_mode)
	{
		play_t_sound(game->audio.ctx, &game->audio.sounds[EATING_ENEMY_SOUND]);
		reset_enemy_position(enemy);
		game->hud.score.value_numeric += ENEMY_REWARD * ++game->ghosts_eaten;
		enemy->panic_mode = 0;
	}
	else
	{
		game->player.health -= 1;
	}
}

void	enemy_check_collision(t_game *game, t_enemy *enemy)
{
	t_list	*enemies;

	enemies = game->map->enemies;
	while (enemies)
	{
		if ((t_enemy *)enemies->content != enemy
			&& fvector_distance(enemy->object->pos,
				((t_enemy *)enemies->content)->object->pos) < PL_RADIUS * 2)
		{
			enemy->object->pos.x -= enemy->delta.x;
			enemy->object->pos.y -= enemy->delta.y;
		}
		enemies = enemies->next;
	}
}

void	enemy_calculate_frame_movement(t_node *node, t_enemy *enemy, int fps)
{
	const t_fvector	e = {1, 0};
	t_fvector		p;
	float			angle;

	if (!node)
		return ;
	p.x = .5f + node->pos.x - enemy->object->pos.x;
	p.y = .5f + node->pos.y - enemy->object->pos.y;
	angle = calculate_angle(e, p);
	enemy->delta.x = cosf(angle) * (EN_SPEED / fps);
	enemy->delta.y = sinf(angle) * (EN_SPEED / fps);
	enemy->object->pos.x += enemy->delta.x;
	enemy->object->pos.y += enemy->delta.y;
}

void	enemy_move_along_path(t_game *game, t_enemy *enemy)
{
	t_node			*node;
	t_list			*deleted_node;

	if (game->panic_mode && get_time() - game->time.pill_time > PANIC_TIME)
		ft_lstclear(&enemy->path, free);
	update_path(game, enemy, &enemy->path);
	if (ft_lstsize(enemy->path))
	{
		node = ((t_node *)enemy->path->content);
		if (fvector_distance((t_fvector){.5f + node->pos.x, .5f + node->pos.y},
			enemy->object->pos) < .1)
		{
			deleted_node = ft_lstpop_front(&enemy->path);
			ft_lstdelone(&deleted_node, free);
			update_path(game, enemy, &enemy->path);
			node = NULL;
			if (ft_lstsize(enemy->path))
				node = ((t_node *)enemy->path->content);
		}
		enemy_calculate_frame_movement(node,
			enemy, game->hud.fps.value_numeric);
	}
}

void	enemy_move(t_game *game)
{
	t_list			*lst;
	t_enemy			*enemy;

	if (get_time() - game->start_game_time > START_GAME_DELAY)
	{
		lst = game->map->enemies;
		while (lst)
		{
			enemy = ((t_enemy *)lst->content);
			enemy_move_along_path(game, enemy);
			enemy->object->distance = distancef(&game->player.pos,
					&enemy->object->pos);
			check_borders_enemy(game, enemy->object);
			if (fvector_distance(game->player.pos, enemy->object->pos) < .7)
				enemy_attack(game, enemy);
			lst = lst->next;
		}
		if (game->panic_mode && get_time() - game->time.pill_time > PANIC_TIME)
		{
			game->panic_mode = 0;
			ft_lstiter(game->map->enemies, reset_panic_mode);
			game->ghosts_eaten = 0;
		}
	}
}
