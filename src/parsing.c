#include "../inc/cub3d.h"

int	get_string_index(char *str, char c)
{
	int	index;
	
	index = -1;
	while (str[++index])
		if (str[index] == c)
			return (index);
	return (-1);
}

void	get_config(t_map* map, int fd, char **line)
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

void	get_textures(t_map *map, int fd)
{
	int		counter;
	char	*line;

	line = NULL;
	counter = -1;
	while (++counter < MAX_WALL_CHARS)
		get_textures_list(map, fd, &line);
	// map->texture_list[0] = get_textures_list(fd, "NO", &line);
	// map->texture_list[1] = get_textures_list(fd, "SO", &line);
	// map->texture_list[2] = get_textures_list(fd, "WE", &line);
	// map->texture_list[3] = get_textures_list(fd, "EA", &line);
	if (line)
		map->F = convert_rgb(crop_prefix(line, "F"));
	else
		map->F = convert_rgb(crop_prefix(skip_empty_lines(fd), "F"));
	map->C = convert_rgb(crop_prefix(skip_empty_lines(fd), "C"));
}

int	is_prefix_number(char *line, char *prefix, int counter)
{
	return (line && !ft_strncmp(line, prefix, ft_strlen(prefix))
		&& (ft_atoi(line + ft_strlen(prefix)) == counter + 1
			|| (counter == 0 && line[ft_strlen(prefix) + 1] == ' ')));
}

char	*get_full_texture_path(char *line, int flag)
{
	char	*new_line;

	new_line = line;
	if (flag) {
		new_line = ft_strcat_delim(ASSETS_PATH, '/', line);
		free(line);
	}
	return (new_line);
}

void	get_textures_list(t_map* map, int fd, char **line)
{
	int		index;

	index = 0;
	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, WALL_PREFIX, ft_strlen(
		WALL_PREFIX)) && get_string_index(WALL_CHARS, (*line)[1]) != -1))
		return ;
	index = get_string_index(WALL_CHARS, (*line)[1]);
	ft_putendl_fd(*line, 1);
	ft_lstadd_back(&map->walls[index].texture, ft_lstnew(get_full_texture_path(
		crop_prefix(*line, WALL_PREFIX), map->path_prefix)));
	*line = skip_empty_lines(fd);
	while (line && *line && !ft_isalpha(**line))
	{
		ft_putendl_fd(*line, 1);
		ft_lstadd_back(&map->walls[index].texture, ft_lstnew(
			get_full_texture_path(*line, map->path_prefix)));
		*line = skip_empty_lines(fd);
	}
}

void	get_entity(t_map* map, int fd, char **line)
{
	int		index;

	index = 0;
	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, ENTITY_PREFIX, ft_strlen(
		ENTITY_PREFIX))))// && get_string_index(WALL_CHARS, (*line)[1]) != -1))
		return ;
	index = ft_atoi(*line + 1) - 1; // Check zero value
	ft_putendl_fd(*line, 1);
	ft_lstadd_back(&map->entity[index].texture, ft_lstnew(get_full_texture_path(
		crop_prefix(*line, ENTITY_PREFIX), map->path_prefix)));
	*line = skip_empty_lines(fd);
	while (line && *line && !ft_isalpha(**line))
	{
		ft_putendl_fd(*line, 1);
		ft_lstadd_back(&map->entity[index].texture, ft_lstnew(
			get_full_texture_path(*line, map->path_prefix)));
		*line = skip_empty_lines(fd);
	}
}

char	**lst_to_char_ptr(t_list *tmp)
{
	char	**map;
	int		counter;
	int		size;

	size = ft_lstsize(tmp);
	map = malloc(sizeof(*map) * (size + 1));
	//TODO: add malloc checking
	counter = -1;
	while (++counter < size)
	{
		map[counter] = tmp->content;
		tmp = tmp->next;
	}
	map[size] = NULL;
	return (map);
}

void	empty_func(void *ptr) //TODO: ??
{
	(void) ptr;
}

int	ft_strrchr_int(const char *line, int chr)
{
	char	*wall;

	wall = ft_strrchr(line, chr);
	if (line && wall)
		return (wall - line + 1);
	return (-1);
}

int	ft_strrchr_int_arr(char *line, char* chr)
{
	int		max;
	int		curr;
	size_t	counter;

	counter = 0;
	max = ft_strrchr_int(line, chr[counter]);
	while (++counter < MAX_WALL_CHARS)
	{
		curr = ft_strrchr_int(line, chr[counter]);
		if (max < curr)
			max = curr;
	}
	return (max);
}

void	map_to_rectangle(t_map *map)
{
	char	**arr;
	char	*resized_line;
	int		i;

	i = -1;
	resized_line = NULL;
	arr = map->map;
	while (arr[++i])
	{
		if (ft_strrchr_int_arr(arr[i], WALL_CHARS) < map->map_size.x || !is_wall(arr[i][ft_strlen(arr[i]) - 1]))
		{
			resized_line = malloc(sizeof(char) * (map->map_size.x + 1));
			if (resized_line == NULL)
				error_exit(NULL, 1, "Memory allocation error: Map processing");
			ft_memset(resized_line, ' ', sizeof(char) * map->map_size.x);
			resized_line[map->map_size.x] = 0;
			ft_memcpy(resized_line, arr[i], ft_strrchr_int_arr(arr[i], WALL_CHARS));
			free(arr[i]);
			arr[i] = resized_line;
		}
	}
}

void	convert_spaces_to_zeros(t_map *map)
{
	char	**arr;
	int		y;
	int		x;

	y = -1;
	arr = map->map;
	while (arr[++y])
	{
		x = -1;
		while (arr[y][++x])
			if (arr[y][x] == ' ')
				arr[y][x] = '0';
	}
}

void	get_map(t_map *map, int fd)
{
	char	*line;
	t_list	*tmp;

	tmp = NULL;
	line = skip_empty_lines(fd);
	while (line && !ft_is_empty(line))
	{
		ft_lstadd_back(&tmp, ft_lstnew(line));
		find_player(map, line, tmp);
		line = skip_empty_lines(fd);
	}
	free(line);
	map->map = lst_to_char_ptr(tmp);
	find_enemy(map);
	ft_lstclear(&tmp, empty_func);
	map->map_size.x = get_map_width((const char **)map->map);
	map->map_size.y = ft_arraylen((void **) map->map);
	map_to_rectangle(map);
}

t_map	*free_map(t_map *map)
{
	if (map)
		ft_freesplit(map->map);
	return (NULL);
}

t_map	*parse_file(int ac, char **av)
{
	t_map	*map;
	int		fd;

	map = NULL;
	fd = check_file(ac, av);
	if (fd != BAD_FILE)
	{
		map = create_empty_map();
		if (map == NULL)
			error_exit(NULL, 1, "Allocation error: Map");
		get_textures(map, fd);
		get_map(map, fd);
		if (map->map_size.x == 0 || map->map_size.y == 0)
			error_exit(NULL, 1, "Reading error: Map");
		if (is_enclosed(map))
		{
			convert_spaces_to_zeros(map);
			return (map);
		}
		else
			error_exit(NULL, 1, "Invalid input file: Map not enclosed");
	}
	else
		error_exit(NULL, 1, "Invalid input file: Map");
	ft_putendl_fd("Reading map: success", 2);
	return (free_map(map));
}
