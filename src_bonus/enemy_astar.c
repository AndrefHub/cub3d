#include "../inc_bonus/cub3d_bonus.h"

t_list	*ft_lstfind(t_list *closed, void *val, int equals(void *, void *))
{
	while (closed)
	{
		if (equals(closed->content, val))
			return (closed);
		closed = closed->next;
	}
	return (NULL);
}

t_node	*ft_nodenew(t_node *data)
{
	t_node	*node;

	node = malloc(sizeof(*node));
	ft_memcpy(node, data, sizeof(*data));
	return (node);
}

void	add_all_neighbours(t_game *game, t_astar_utils *lists, t_node *node, t_vector player)
{
	int			counter;
	t_vector	pos;
	t_list		*lst;

	counter = -3;
	while (++counter < 3)
	{
		if (counter)
		{
			pos.y = node->pos.y + counter / 2;
			pos.x = node->pos.x + (counter % 2);
			if (0 <= pos.x && pos.x < game->map->map_size.x && 0 <= pos.y &&
				pos.y < game->map->map_size.y && !is_wall(game->map->map[pos.y]
				[pos.x]) && !ft_lstfind(lists->closed, (void *)(&pos), pos_equals))
			{
				lst = ft_lstfind(lists->open, (void *)(&pos), pos_equals);
				if (lst && ((t_node *)lst->content)->g > node->g + 1)
						((t_node *)lst->content)->g = node->g + 1;
				if (!lst)
					ft_lstadd_front(&lists->open, ft_lstnew(ft_nodenew(&(t_node){pos,
						node->g + 1, heuristic_cost(pos, player), node})));
			}
		}
	}
}

t_list	*astar_regenerate_path(t_list *curr)
{
	t_list	*path;
	t_node	*node;

	path = NULL;
	node = ((t_node *)curr->content);
	while (node)
	{
		ft_lstadd_front(&path, ft_lstnew(ft_nodenew(node)));
		node = node->parent;
	}
	return (path);
}

// returns first five nodes of shortest path
t_list	*astar(t_game *game, t_vector enemy, t_vector player)
{
	t_astar_utils	lists;
	t_list			*curr;
	t_list			*path;

	lists.open = NULL;
	lists.closed = NULL;
	ft_lstadd_back(&lists.open, ft_lstnew(ft_nodenew(&(t_node){enemy, 0,
									heuristic_cost(enemy, player), NULL})));
	while (ft_lstsize(lists.open))
	{
		ft_lstsort(&lists.open, node_comparator);
		curr = ft_lstpop_front(&lists.open);
		ft_lstadd_front(&lists.closed, curr);
		if (heuristic_cost(((t_node *)curr->content)->pos, player) <= 0)
		{
			path = astar_regenerate_path(curr);
			ft_lstclear(&lists.open, free);
			ft_lstclear(&lists.closed, free);
			return (path);
		}
		add_all_neighbours(game, &lists, curr->content, player);
	}
	ft_lstclear(&lists.open, free);
	ft_lstclear(&lists.closed, free);
	return (NULL);
}