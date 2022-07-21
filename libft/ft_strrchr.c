/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:01:13 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 00:01:14 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	l;

	l = ft_strlen(s);
	while (s[l] != (char)c && l != 0)
		l--;
	if (s[l] == (char)c)
		return ((char *)s + l);
	return (NULL);
}
