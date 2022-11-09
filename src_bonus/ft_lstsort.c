/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:17 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:49:21 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static int	sort(t_list **begin, t_list *cur, t_list *next, int (*cmp)())
{
	int		sorted;
	t_list	*prev;

	prev = NULL;
	sorted = 1;
	while (next)
	{
		if ((*cmp)(cur->content, next->content) != 0)
		{
			sorted = 0;
			if (prev)
				prev->next = next;
			else
				*begin = next;
			cur->next = next->next;
			next->next = cur;
			prev = next;
			next = cur->next;
			continue ;
		}
		prev = cur;
		cur = next;
		next = cur->next;
	}
	return (sorted);
}

void	ft_lstsort(t_list **lst, int (*cmp)())
{
	if (!cmp || !*lst)
		return ;
	while (sort(lst, *lst, (*lst)->next, cmp) == 0)
		;
}
