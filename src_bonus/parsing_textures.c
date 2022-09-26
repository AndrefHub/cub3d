#include "../inc_bonus/cub3d_bonus.h"

void	parse_config(t_map* map, int fd, char **line)
{
	if (!*line)
		*line = skip_empty_lines(fd);
	while (*line && ft_strncmp(*line, WALL_PREFIX, ft_strlen(WALL_PREFIX)) && 
		!(map->bonus && map->path_prefix))
	{
		if (!ft_strncmp(*line, USE_PATH_PREFIX, ft_strlen(USE_PATH_PREFIX)))
			++map->path_prefix;
		else if (!ft_strncmp(*line, BONUS, ft_strlen(BONUS)))
			++map->bonus;
		free(*line);
		*line = skip_empty_lines(fd);
	}
}

void	parse_walls(t_map* map, int fd, char **line)
{
	int		index;

	index = 0;
	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, WALL_PREFIX, ft_strlen(
		WALL_PREFIX)) && get_string_index(WALL_CHARS, (*line)[1]) != -1))
		return ;
	index = get_string_index(WALL_CHARS, (*line)[1]);
	if (index < 0)
		error_exit(NULL, 1, "wrong index map");
	ft_lstadd_back(&map->walls[index].texture, ft_lstnew(get_full_texture_path(
		crop_prefix(*line, WALL_PREFIX), map->path_prefix)));
	*line = skip_empty_lines(fd);
	while (line && *line && !ft_isalpha(**line))
	{
		ft_lstadd_back(&map->walls[index].texture, ft_lstnew(
			get_full_texture_path(*line, map->path_prefix)));
		*line = skip_empty_lines(fd);
	}
} 

void	parse_enemies(t_map* map, int fd, char **line)
{
	int		index;

	index = 0;
	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, OBJECT_PREFIX, ft_strlen(
		OBJECT_PREFIX))))// && get_string_index(WALL_CHARS, (*line)[1]) != -1))
		return ;
	index = ft_atoi(*line + 1) - 1; // Check zero value
	if (index < 0)
		error_exit(NULL, 1, "wrong index map");
	ft_lstadd_back(&map->object[index].texture, ft_lstnew(get_full_texture_path(
		crop_prefix(*line, OBJECT_PREFIX), map->path_prefix)));
	*line = skip_empty_lines(fd);
	while (line && *line && !ft_isalpha(**line))
	{
		ft_lstadd_back(&map->object[index].texture, ft_lstnew(
			get_full_texture_path(*line, map->path_prefix)));
		*line = skip_empty_lines(fd);
	}
}

void	parse_smth(t_map* map, int fd, char **line, t_parse_info info)
{
	int		index;

	index = 0;
	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, info.prefix, ft_strlen(
		info.prefix))))
		return ;
	if (info.chars)
		index = get_string_index(info.chars, (*line)[1]);
	else
		index = ft_atoi(*line + 1) - 1; // Check zero value;
	if (index < 0)
		error_exit(NULL, 1, "wrong index map");
	ft_lstadd_back(&(info.arr)[index].texture, ft_lstnew(get_full_texture_path(
		crop_prefix(*line, info.prefix), map->path_prefix)));
	*line = skip_empty_lines(fd);
	while (line && *line && !ft_isalpha(**line))
	{
		ft_lstadd_back(&(info.arr)[index].texture, ft_lstnew(
			get_full_texture_path(*line, map->path_prefix)));
		*line = skip_empty_lines(fd);
	}
}

void	parse_sounds(t_map* map, int fd, char **line)
{
	int		index;

	index = 0;
	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, SOUND_PREFIX, ft_strlen(
		SOUND_PREFIX)) )) // && get_string_index(WALL_CHARS, (*line)[1]) != -1))
		return ;
	index = ft_atoi(*line + 1) - 1; // Check zero value
	if (index < 0)
		error_exit(NULL, 1, "wrong index map");
	ft_putendl_fd(*line, 1);
	map->sounds[index] = get_full_texture_path(
		crop_prefix(*line, SOUND_PREFIX), map->path_prefix);
	*line = skip_empty_lines(fd);
}

void	parse_assets(t_map *map, int fd)
{
	int		counter;
	char	*line;

	line = NULL;
	counter = -1;
	parse_config(map, fd, &line);
	while (++counter < MAX_WALL_CHARS)
		parse_smth(map, fd, &line, (t_parse_info){WALL_CHARS, WALL_PREFIX, (t_texture *)map->walls});
		// parse_walls(map, fd, &line);
	counter = -1;
	while (++counter < MAX_OBJECTS)
		parse_smth(map, fd, &line, (t_parse_info){NULL, OBJECT_PREFIX, (t_texture *)map->object});
	// parse_enemies(map, fd, &line);
	parse_font(map, fd, &line);
	parse_sounds(map, fd, &line);
	parse_sounds(map, fd, &line);
	if (line)
		map->f = convert_to_rgb(crop_prefix(line, "F"));
	else
		map->f = convert_to_rgb(crop_prefix(skip_empty_lines(fd), "F"));
	map->c = convert_to_rgb(crop_prefix(skip_empty_lines(fd), "C"));
}