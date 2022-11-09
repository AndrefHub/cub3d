/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_font.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:12 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:50:14 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

// char	*skip_empty_chars(char *line)
// {
// 	char	*skipped;
// 	char	*copy;

// 	copy = line;
// 	while (is_space(*line))
// 		++line;
// 	skipped = malloc(sizeof(*skipped) * (ft_strlen(line) + 1));
// 	ft_strlcpy(skipped, line, ft_strlen(line));
// 	free(copy);
// 	return (skipped);
// }

void	parse_font(t_map *map, int fd, char **line)
{
	int		index;

	index = -1;
	if (!*line)
		*line = skip_empty_lines(fd);
	while (line && *line && !ft_strncmp(*line, FONT_PREFIX,
			ft_strlen(FONT_PREFIX)))
	{
		index = (*line)[1] - FONT_OFFSET;
		if (0 <= index && index < MAX_FONT_CHARS)
			ft_lstadd_back(&map->font[index].texture,
				ft_lstnew(ft_strdup(*line + 3)));
		free(*line);
		*line = skip_empty_lines(fd);
	}	
}
