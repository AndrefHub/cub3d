#include "../inc_bonus/cub3d_bonus.h"

int	node_comparator(t_node *lhs, t_node *rhs)
{
	return (lhs->h > rhs->h);
}

int	pos_equals(void *lhs, void *rhs)
{
	return (((t_node *)lhs)->pos.x == ((t_vector *)rhs)->x
		&& ((t_node *)lhs)->pos.y == ((t_vector *)rhs)->y);
}

// Manhattan distance
int	heuristic_cost(t_vector lhs, t_vector rhs)
{
	return (abs(lhs.x - rhs.x) + abs(lhs.y - rhs.y));
}

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

void	add_all_neighbours(t_game *game, t_list **open, t_list *closed,
		t_node *node, t_vector player)
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
			if (!is_wall(game->map->map[pos.y][pos.x])
				&& !ft_lstfind(closed, (void *)(&pos), pos_equals))
			{
				lst = ft_lstfind(*open, (void *)(&pos), pos_equals);
				if (lst)
				{
					if (((t_node *)lst->content)->g > node->g + 1)
						((t_node *)lst->content)->g = node->g + 1;
				}
				else
					ft_lstadd_front(open, ft_lstnew(ft_nodenew(&(t_node){pos,
						node->g + 1, heuristic_cost(pos, player), node})));
			}
		}
	}
}

t_list	*get_first_n_nodes(t_list *lst, int n)
{
	int		counter;
	t_list	*to_delete;
	t_list	*tmp;

	counter = 0;
	tmp = lst;
	if (!tmp)
		return (tmp);
	while (tmp->next && ++counter < n)
	{
		tmp = tmp->next;
	}
	to_delete = tmp->next;
	tmp->next = NULL;
	ft_lstclear(&to_delete, free);
	return (lst);
}

// returns first five nodes of shortest path
t_list	*astar(t_game *game, t_vector enemy, t_vector player)
{
	t_list	*open;
	t_list	*closed;
	t_list	*curr;
	t_list	*path;
	t_node	*node;

	t_ull time = get_time_hp();
	open = NULL;
	closed = NULL;
	path = NULL;
	ft_lstadd_back(&open, ft_lstnew(ft_nodenew(&(t_node){enemy, 0,
									heuristic_cost(enemy, player), NULL})));
	while (ft_lstsize(open))
	{
		ft_lstsort(&open, node_comparator);
		curr = ft_lstpop_front(&open);
		ft_lstadd_front(&closed, curr);
		if (heuristic_cost(((t_node *)curr->content)->pos, player) <= 0)
		{
			node = ((t_node *)curr->content);
			while (node)
			{
				ft_lstadd_front(&path, ft_lstnew(ft_nodenew(node)));
				node = node->parent;
			}
			ft_lstclear(&open, free);
			ft_lstclear(&closed, free);
			printf("%llu\n", get_time_hp() - time);
			return (path);
		}
		add_all_neighbours(game, &open, closed, curr->content, player);
	}
	ft_lstclear(&open, free);
	ft_lstclear(&closed, free);
	return (NULL);
}