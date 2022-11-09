/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_astar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:48:58 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:49:00 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	node_comparator(t_node *lhs, t_node *rhs)
{
	if (lhs->h == rhs->h)
		return (lhs->g > rhs->g);
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
