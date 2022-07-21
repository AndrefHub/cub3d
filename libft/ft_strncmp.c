/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:00:59 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 00:01:02 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	while (n && *s1 != '\0' && *s2 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0 || *(unsigned char *)s1 - *(unsigned char *) s2 == 0)
		return (0);
	else if (*(unsigned char *)s1 - *(unsigned char *) s2 > 0)
		return (1);
	return (-1);
}
