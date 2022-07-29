/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:53:46 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 20:53:47 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*buf;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	buf = (char *) malloc(len * sizeof(char));
	if (buf == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		buf[i] = *s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		buf[i] = *s2++;
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
