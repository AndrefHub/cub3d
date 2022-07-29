/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:57:27 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/12 23:57:29 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc( size_t number, size_t size)
{
	char	*buf;

	buf = (char *) malloc(number * size);
	if (buf == NULL)
		return (NULL);
	ft_memset(buf, 0, number * size);
	return ((void *)buf);
}
