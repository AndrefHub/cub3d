/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:09:52 by lsherry           #+#    #+#             */
/*   Updated: 2022/09/29 12:30:44 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop_front(t_list **lst)
{
	t_list	*pop;

	pop = *lst;
	*lst = (*lst)->next;
	pop->next = NULL;
	return (pop);
}
