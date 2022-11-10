/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:14 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:12:49 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	parse_config(t_map *map, int fd, char **line)
{
	if (!*line)
		*line = skip_empty_lines(fd);
	while (*line && ft_strncmp(*line, WALL_PREFIX, ft_strlen(WALL_PREFIX))
		&& !(map->bonus && map->path_prefix))
	{
		if (!ft_strncmp(*line, USE_PATH_PREFIX, ft_strlen(USE_PATH_PREFIX)))
			++map->path_prefix;
		else if (!ft_strncmp(*line, BONUS, ft_strlen(BONUS)))
			++map->bonus;
		free(*line);
		*line = skip_empty_lines(fd);
	}
}

void	parse_texture_list_array(int fd, char **line, t_parse_info info)
{
	int		index;

	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, info.prefix,
				ft_strlen(info.prefix))))
		return ;
	if (info.chars)
		index = get_string_index(info.chars, (*line)[1]);
	else
		index = ft_atoi(*line + 1) - 1;
	if (index < 0 || index >= info.size)
		error_exit(NULL, 1, "wrong index map");
	ft_lstadd_back(&(info.arr)[index].texture,
		ft_lstnew(crop_prefix(*line, info.prefix)));
	*line = skip_empty_lines(fd);
	while (line && *line && !ft_isalpha(**line))
	{
		ft_lstadd_back(&(info.arr)[index].texture, ft_lstnew(*line));
		*line = skip_empty_lines(fd);
	}
}

void	parse_texture(int fd, char **line, t_parse_info info)
{
	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, info.prefix,
				ft_strlen(info.prefix))))
		return ;
	ft_lstadd_back(&(info.arr->texture),
		ft_lstnew(crop_prefix(*line, info.prefix)));
	*line = NULL;
}

void	parse_sounds(t_map *map, int fd, char **line)
{
	int		index;

	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, SOUND_PREFIX,
				ft_strlen(SOUND_PREFIX))))
		return ;
	index = ft_atoi(*line + 1) - 1;
	if (index < 0 || index >= MAX_SOUNDS)
		error_exit(NULL, 1, "wrong index map");
	if (map->sounds[index])
		free(*line);
	else
		map->sounds[index] = crop_prefix(*line, SOUND_PREFIX);
	*line = skip_empty_lines(fd);
}

void	parse_assets(t_map *map, int fd)
{
	int		counter;
	char	*line;

	line = NULL;
	counter = -1;
	while (++counter < MAX_WALL_CHARS)
		parse_texture_list_array(fd, &line, (t_parse_info){WALL_CHARS,
			WALL_PREFIX, (t_texture *)map->walls, ft_strlen(WALL_CHARS)});
	counter = -1;
	while (++counter < MAX_OBJECTS)
		parse_texture_list_array(fd, &line, (t_parse_info){NULL,
			OBJECT_PREFIX, (t_texture *)map->object, MAX_OBJECTS});
	parse_font(map, fd, &line);
	counter = -1;
	while (++counter < MAX_SOUNDS)
		parse_sounds(map, fd, &line);
	parse_texture(fd, &line, (t_parse_info){NULL, "F", &map->floor, 0});
	parse_texture(fd, &line, (t_parse_info){NULL, "C", &map->ceiling, 0});
	check_assets(map);
}
