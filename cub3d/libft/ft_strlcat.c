/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:00:31 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 00:00:32 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*tmp_dest;
	const char	*tmp_src;
	size_t		n;
	size_t		dst_len;

	n = size;
	tmp_dest = dst;
	tmp_src = src;
	while (n-- != 0 && *tmp_dest != '\0')
		tmp_dest++;
	dst_len = tmp_dest - dst;
	n = size - dst_len;
	if (n == 0)
		return (dst_len + ft_strlen(tmp_src));
	while (*tmp_src != '\0')
	{
		if (n != 1)
		{
			*tmp_dest++ = *tmp_src;
			n--;
		}
		tmp_src++;
	}
	*tmp_dest = '\0';
	return (dst_len + (tmp_src - src));
}
