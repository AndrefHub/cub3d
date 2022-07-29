/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:52:18 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 20:52:28 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*buf;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s) + 1;
	buf = (char *) malloc(sizeof(char) * len);
	if (!buf)
		return (NULL);
	i = -1;
	while (++i < len - 1)
		buf[i] = f(i, s[i]);
	buf[i] = '\0';
	return (buf);
}
