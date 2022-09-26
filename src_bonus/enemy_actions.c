#include "../inc_bonus/cub3d_bonus.h"

void	enemy_attack(t_game *game, t_enemy *enemy)
{
	(void)game;
	if (get_time() - game->player.last_attack_time > PL_INVINCIBILITY &&
		get_time() - enemy->last_attack_time > ENEMY_RELOAD)
	{
		game->player.last_attack_time = get_time();
		enemy->last_attack_time = get_time();
		game->hud.health.value -= 1;
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

void	enemy_move(t_game *game)
{
	t_list			*lst;
	const t_fvector	e = {1, 0};
	t_enemy			*enemy;
	t_fvector		p;
	float 			angle;

	lst = game->map->enemies;
	while (lst)
	{
		enemy = ((t_enemy *)lst->content);
		p.x = game->player.pos.x - enemy->object->pos.x;
		p.y = game->player.pos.y - enemy->object->pos.y;
		angle = calculate_angle(e, p);
		enemy->delta.x = cosf(angle) * EN_SPEED;
		enemy->delta.y = sinf(angle) * EN_SPEED;

		enemy->object->pos.x += enemy->delta.x;
		enemy->object->pos.y += enemy->delta.y;
		enemy->object->distance = distancef(&game->player.pos, &enemy->object->pos);
		check_borders(game, enemy->object);
		if (fvector_distance(game->player.pos, enemy->object->pos) < 1)
			enemy_attack(game, enemy);
		lst = lst->next;
	}
}
