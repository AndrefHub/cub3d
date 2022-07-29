/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:59:31 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/12 23:59:34 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_mem;

	if (!dst && !src)
		return (NULL);
	tmp_mem = (unsigned char *)dst;
	while (n--)
	{
		*tmp_mem = *(unsigned char *)src++;
		tmp_mem++;
	}
	return (dst);
}
