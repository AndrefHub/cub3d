/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:55:54 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/02 11:32:51 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	len;
	size_t	i;
	char	*buf;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	tmp = s1;
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	buf = (char *) malloc(len * sizeof(char) + 1);
	if (!buf)
		return (NULL);
	while (*s1 != '\0')
		buf[i++] = *s1++;
	while (*s2 != '\0')
		buf[i++] = *s2++;
	buf[i] = '\0';
	free(tmp);
	return (buf);
}
