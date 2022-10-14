#include "../inc_bonus/cub3d_bonus.h"

void	enemy_attack(t_game *game, t_enemy *enemy)
{
//	if (game->panic_mode)
//	{
//		reset_enemy_position(enemy);
//		game->hud.score.value_numeric += 200 * ++game->ghosts_eaten;
//	}
//	else
	if (get_time() - game->player.last_attack_time > PL_INVINCIBILITY &&
		get_time() - enemy->last_attack_time > ENEMY_RELOAD)
	{
		game->player.last_attack_time = get_time();
		enemy->last_attack_time = get_time();
		game->hud.health.value_numeric -= 1;
		ft_putendl_fd("Enemy attacked you", 1);
	}
}

float	calculate_angle(t_fvector p, t_fvector e)
{
	const float	multiplication = p.x * e.x + p.y * e.y;
	const float	determinant = p.x * e.y - p.y * e.x;
	float atan;

	atan = (atan2(determinant, multiplication));
	if (atan < 0)
		atan += 2 * PI;
	return (atan);
}

void	update_path(t_game *game, t_enemy *enemy, t_list **path)
{
	if (!ft_lstsize(*path))
	{
		*path = enemy->pathfinding_algorithm(game, enemy);
	}
}

void	enemy_check_collision(t_game *game, t_enemy *enemy)
{
	t_list	*enemies;
	
	enemies = game->map->enemies;
	while (enemies)
	{
		if ((t_enemy *)enemies->content != enemy && fvector_distance(enemy->object->pos, ((t_enemy *)enemies->content)->
			object->pos) < PL_RADIUS * 2)
		{
			enemy->object->pos.x -= enemy->delta.x;
			enemy->object->pos.y -= enemy->delta.y;
		}
		enemies = enemies->next;
	}
}

void	enemy_move_along_path(t_game *game, t_enemy *enemy)
{
	const t_fvector	e = {1, 0};
	t_fvector		p;
	t_node			*node;
	float 			angle;

	if (game->panic_mode && get_time() - game->time.pill_time > PANIC_TIME)
		ft_lstclear(&enemy->path, free);
	update_path(game, enemy, &enemy->path);
	if (ft_lstsize(enemy->path))
	{
		node = ((t_node *)enemy->path->content);
		if (fvector_distance((t_fvector){.5f + node->pos.x, .5f + node->pos.y},
			enemy->object->pos) < .1)
		{
			ft_lstdelone(ft_lstpop_front(&enemy->path), free);
			update_path(game, enemy, &enemy->path);
			node = NULL;
			if (ft_lstsize(enemy->path))
				node = ((t_node *)enemy->path->content);;
		}
		if (!node)
			return ;
		p.x = .5f + node->pos.x - enemy->object->pos.x;
		p.y = .5f + node->pos.y - enemy->object->pos.y;
		angle = calculate_angle(e, p);
		enemy->delta.x = cosf(angle) * EN_SPEED;
		enemy->delta.y = sinf(angle) * EN_SPEED;
		enemy->object->pos.x += enemy->delta.x;
		enemy->object->pos.y += enemy->delta.y;
		enemy->object->distance = distancef(&game->player.pos, &enemy->object->pos);
	}
	// enemy_check_collision(game, enemy);
}

void	enemy_move(t_game *game)
{
	t_list			*lst;
	t_enemy			*enemy;

	lst = game->map->enemies;
	while (lst)
	{
		enemy = ((t_enemy *)lst->content);
		enemy_move_along_path(game, enemy);
		check_borders(game, enemy->object);
		if (fvector_distance(game->player.pos, enemy->object->pos) < .7)
			enemy_attack(game, enemy);
		lst = lst->next;
	}
	if (game->panic_mode && get_time() - game->time.pill_time > PANIC_TIME)
	{
		game->panic_mode = 0;
		game->ghosts_eaten = 0;
	}
}
