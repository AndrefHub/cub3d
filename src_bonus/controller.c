/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:47 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:47:48 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"
#include <unistd.h>

void	open_door(t_game *game)
{
	const int	x = (int)game->player.pos.x;
	const int	y = (int)game->player.pos.y;
	const float	angle = game->player.angle;
	char		*to_change;

	to_change = NULL;
	if (PI / 4 <= angle && angle <= 3 * PI / 4 && ft_tolower(game->grid
			[y + 1][x]) == 'd')
		to_change = game->grid[y + 1] + x;
	else if (3 * PI / 4 <= angle && angle <= 5 * PI / 4 && ft_tolower(game->grid
			[y][x - 1]) == 'd')
		to_change = game->grid[y] + x - 1;
	else if (5 * PI / 4 <= angle && angle <= 7 * PI / 4 && ft_tolower(game->grid
			[y - 1][x]) == 'd')
		to_change = game->grid[y - 1] + x;
	else if ((7 * PI / 4 <= angle || angle <= PI / 4) && ft_tolower(game->grid
			[y][x + 1]) == 'd')
		to_change = game->grid[y] + x + 1;
	if (to_change && *to_change == 'd')
		*to_change = 'D';
	else if (to_change && *to_change == 'D')
		*to_change = 'd';
}

// void	change_objects_textures(t_game *game)
// {
// 	t_list		*obj_list;
// 	t_object	*object;

// 	obj_list = game->objects;
// 	while (obj_list)
// 	{
// 		object = obj_list->content;
// 		game->map->enemy->img = game->map->enemy->img->next;
// 		object->sprite = game->map->enemy->img->content;
// 		obj_list = obj_list->next;
// 	}
// 	(void) game;
// }

inline void	change_enemies_textures_panic_mode(t_game *game)
{
	t_list	*enemies;
	t_enemy	*enemy;
	int		type;
	
	enemies = game->map->enemies;
	while (enemies)
	{
		enemy = enemies->content;
		type = enemy->object->type;
		if (enemy->panic_mode)
			type = MAX_PILLS - 1;
		enemy->object->sprite = (t_img *)game->map->object[type].img->content;
		enemies = enemies->next;
	}
}

inline void	change_objects_textures(t_game *game, int frames_to_move)
{
	t_list		*objects;
	t_object	*object;
	int			index;
	int			counter;

	objects = game->objects;
	index = -1;
	while (++index < ft_min(MAX_PILLS + game->enemies_count, MAX_OBJECTS))
	{
		counter = -1;
		while (++counter < frames_to_move)
			game->map->object[index].img = game->map->object[index].img->next;		
	}
	while (objects)
	{
		object = objects->content;
		object->sprite = (t_img *)game->map->object[object->type].img->content;
		objects = objects->next;
	}
	change_enemies_textures_panic_mode(game);
}

// would be reasonable to change game->textures to be pointer array
inline void	change_walls_textures(t_game *game, int frames_to_move)
{
	int		index;
	int		counter;

	index = -1;
	while (++index < MAX_WALL_CHARS)
	{
		counter = -1;
		while (++counter < frames_to_move)
			game->map->walls[index].img = game->map->walls[index].img->next;
		game->textures[index] = *(t_img *)game->map->walls[index].img->content;
	}
}

void	change_textures(t_game *game)
{
	const float	clocks_per_frame = 1000. / FRAMERATE;
	// static int	s = 0;
	int			frames_to_move;

	frames_to_move = (int)((float)(get_time() - game->time.startup)
			/ clocks_per_frame) - (int)((float)
			(game->time.last - game->time.startup) / clocks_per_frame);
	if (frames_to_move)
	{
		change_walls_textures(game, frames_to_move);
		change_objects_textures(game, frames_to_move);
	}
	// ++s;
}
