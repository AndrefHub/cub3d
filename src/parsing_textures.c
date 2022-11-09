/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:13 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:47:14 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*parse_texture(int fd, char **line, char *prefix)
{
	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, prefix,
				ft_strlen(prefix))))
		return (NULL);
	return (crop_prefix(*line, prefix));
}

void	parse_assets(t_map *map, int fd)
{
	char	*line;

	line = NULL;
	map->walls[0].texture = parse_texture(fd, &line, "NO");
	line = NULL;
	map->walls[1].texture = parse_texture(fd, &line, "SO");
	line = NULL;
	map->walls[2].texture = parse_texture(fd, &line, "WE");
	line = NULL;
	map->walls[3].texture = parse_texture(fd, &line, "EA");
	map->f = convert_to_rgb(crop_prefix(skip_empty_lines(fd), "F"));
	map->c = convert_to_rgb(crop_prefix(skip_empty_lines(fd), "C"));
}
