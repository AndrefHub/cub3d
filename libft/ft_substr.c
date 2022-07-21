/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:41:19 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 20:41:20 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (slen < start)
	{
		buf = (char *) malloc(sizeof(char));
		buf[0] = '\0';
		return (buf);
	}
	if (slen - start < len)
		len = slen - start;
	buf = (char *)malloc(len + 1);
	if (!buf)
		return (NULL);
	while (len > i && s[start] && start < slen)
	{
		buf[i++] = s[start++];
	}
	buf[i] = '\0';
	return (buf);
}
