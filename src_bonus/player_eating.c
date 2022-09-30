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
		ft_lstdelone(curr, del);
		return ;
	}
	while (curr)
	{
		if (curr == to_del)
		{
			prev->next = curr->next;
			ft_lstdelone(curr, del);
			return ;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	eat_by_coords(t_game *game, t_vector pos)
{
	t_list      *objects;
	t_object    *object;

	objects = game->objects;
	while (objects)
	{
		object = objects->content;
		if ((int)object->pos.x == pos.x && (int)object->pos.y == pos.y)
		{
			game->hud.score.value += 100 + (game->map->map[pos.y][pos.x] == 'o') * 400;
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