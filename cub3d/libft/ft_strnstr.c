/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:01:05 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 00:01:11 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (*needle == '\0' || haystack == needle)
		return ((char *)haystack);
	if (ft_strlen(haystack))
	{
		i = 0;
		while (len - i >= needle_len && i < len)
		{
			if (ft_strncmp((char *)haystack, (char *)needle, needle_len) == 0)
				return ((char *)haystack);
			haystack++;
			++i;
		}
	}
	return (NULL);
}
