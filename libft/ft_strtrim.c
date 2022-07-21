/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:40:45 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 20:40:49 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcont(char c, char const *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	char	*buf;
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	begin = 0;
	end = ft_strlen(s1);
	while (begin < end && ft_strcont(s1[begin], set))
		begin++;
	while (begin < end && ft_strcont(s1[end - 1], set))
		end--;
	buf = (char *) malloc((end - begin + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (begin + i < end)
	{
		buf[i] = s1[begin + i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
