/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_eating.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:30 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:11:15 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	ft_lstdelbyaddr(t_list **lst, t_list *to_del, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	prev = *lst;
	curr = *lst;
	if (curr == to_del)
	{
		*lst = curr->next;
		ft_lstdelone(&curr, del);
		return ;
	}
	while (curr)
	{
		if (curr == to_del)
		{
			prev->next = curr->next;
			ft_lstdelone(&curr, del);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	set_panic_mode(t_game *game)
{
	t_list		*enemies;
	t_enemy		*enemy;
	t_vector	pos;
	int			counter;

	counter = 0;
	game->time.pill_time = get_time();
	game->panic_mode = 1;
	enemies = game->map->enemies;
	while (enemies)
	{
		pos.x = (counter % 2) * (game->map->map_size.x - 3) + 1;
		pos.y = ((counter / 2) % 2) * (game->map->map_size.y - 3) + 1;
		enemy = enemies->content;
		if (enemy)
		{
			ft_lstclear(&enemy->path, free);
			if (!is_wall(game->map->map[pos.y][pos.x]))
				enemy->path = astar(game, (t_vector)
					{enemy->object->pos.x, enemy->object->pos.y}, pos);
			enemy->panic_mode = 1;
		}
		enemies = enemies->next;
		++counter;
	}
}

void	eat_pill_sound_effect(t_game *game)
{
	play_t_sound(game->audio.ctx, &game->audio.sounds[EATING_SOUND]);
	if (game->audio.sounds[EATING_SOUND].play)
	{
		game->audio.sounds[EATING_SOUND].play->volume0 = .5;
		game->audio.sounds[EATING_SOUND].play->volume1 = .5;
	}
}

void	eat_by_coords(t_game *game, t_vector pos)
{
	t_list		*objects;
	t_object	*object;

	objects = game->objects;
	while (objects)
	{
		object = objects->content;
		if (object->type < MAX_PILLS && (int)object->pos.x == pos.x
			&& (int)object->pos.y == pos.y)
		{
			--game->objects_count;
			eat_pill_sound_effect(game);
			game->hud.score.value_numeric += COIN_REWARD + (game->map->map
				[pos.y][pos.x] == 'o') * (PILL_REWARD - COIN_REWARD);
			if (game->map->map[pos.y][pos.x] == 'o')
				set_panic_mode(game);
			ft_lstdelbyaddr(&game->objects, objects, free);
			game->map->map[pos.y][pos.x] = '0';
			return ;
		}
		objects = objects->next;
	}
}

void	player_eat(t_game *game)
{
	const t_vector	pos = {game->player.pos.x, game->player.pos.y};

	if (is_edible(game->map->map[pos.y][pos.x]))
	{
		eat_by_coords(game, pos);
	}
}
