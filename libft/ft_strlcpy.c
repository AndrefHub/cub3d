/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:00:34 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 00:00:37 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char		*tmp_dest;
	const char	*tmp_src;
	size_t		n;

	n = size;
	tmp_dest = dst;
	tmp_src = src;
	if (n != 0)
	{
		while (*tmp_src != '\0' && --n != 0)
			*tmp_dest++ = *tmp_src++;
	}
	if (size != 0)
		*tmp_dest = '\0';
	return (ft_strlen(src));
}
