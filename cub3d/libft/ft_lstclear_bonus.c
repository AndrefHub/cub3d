/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:07:48 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 21:07:55 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*copy;

	copy = *lst;
	while (copy)
	{
		elem = copy->next;
		if (copy->content)
			del(copy->content);
		free(copy);
		copy = elem;
	}
	*lst = ((void *)0);
}
