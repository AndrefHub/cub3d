/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:00:27 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/02 11:32:57 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	len;
	char			*dup;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	dup = (char *) malloc(len + 1 * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		dup[i] = *(char *)(s + i);
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
