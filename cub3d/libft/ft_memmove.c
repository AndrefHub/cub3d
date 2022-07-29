/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:59:57 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 00:00:01 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*ret;

	ret = dst;
	if (!dst && !src)
		return (NULL);
	if (dst <= src || (char *) dst >= ((char *) src + len))
	{
		while (len--)
		{
			*(char *) dst++ = *(char *) src++;
		}
	}
	else
	{
		dst = (char *) dst + len - 1;
		src = (char *) src + len - 1;
		while (len--)
		{
			*(char *) dst-- = *(char *) src--;
		}
	}
	return (ret);
}
