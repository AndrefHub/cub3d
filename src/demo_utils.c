/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:46:39 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:46:40 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**charlist_to_matrix(t_list *list)
{
	int		length;
	int		i;
	char	**matrix;

	length = ft_lstsize(list);
	matrix = (char **) malloc(sizeof(char *) * length + 1);
	if (matrix == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		matrix[i] = list->content;
		list = list->next;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
