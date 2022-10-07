#include "../inc_bonus/cub3d_bonus.h"

void	reset_enemy_position(void *enemy)
{
	t_enemy	*en;

	en = enemy;
	en->object->pos = en->starting_pos;
	ft_lstclear(&en->path, free);
}

void	reset_positions(t_game *game)
{
	t_list	*enemies;

	game->player.pos = game->player.starting_pos;
	enemies = game->map->enemies;
	ft_lstiter(enemies, reset_enemy_position);
}

int	player_respawn(t_game *game)
{
	if (game->hud.lives.value > 0)
	{
		game->hud.health.value = MAX_HEALTH;
		--game->hud.lives.value;
		reset_positions(game);
		return (1);
	}
	return (0);
}