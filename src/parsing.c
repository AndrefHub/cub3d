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

void	get_textures(t_map *map, int fd)
{
	int		counter;
	char	*line;

	line = NULL;
	counter = -1;
	ft_putendl_fd("Are we even here?", 2);
	while (++counter < MAX_WALL_CHARS)
		get_textures_list(map, fd, &line);
	// map->texture_list[counter] = get_textures_list(fd, (char []){'W', 'D', '\0'}, &line);
		
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
		&& (ft_atoi(line + ft_strlen(prefix)) == counter
			|| (counter == 0 && line[ft_strlen(prefix) + 1] == ' ')));
}

void	get_textures_list(t_map* map, int fd, char **line)
{
	// t_list		*lst;
	char	*prefix = WALL_PREFIX;
	int		index;

	// lst = NULL;
	index = 0;
	if (!line || !*line)
		*line = skip_empty_lines(fd);
	if (line && *line && **line == 'W' && get_string_index(WALL_CHARS, (*line)[1]) != -1)
	{
		index = get_string_index(WALL_CHARS, (*line)[1]);
		ft_putendl_fd(*line, 1);
		ft_lstadd_back(&map->texture_list[index], ft_lstnew(crop_prefix(*line, prefix)));
	}
	else
		return ;
	*line = skip_empty_lines(fd);
	while (line && *line && !ft_isalpha(**line))
	{
		ft_putendl_fd(*line, 1);
		ft_lstadd_back(&map->texture_list[index], ft_lstnew(*line));
		*line = skip_empty_lines(fd);
	}
	ft_putstr_fd("--- Wall ", 1);
	ft_putnbr_fd(index, 1);
	ft_putendl_fd(" done ---", 1);
}

char	**lst_to_char_ptr(t_list *tmp)
{
	char	**map;
	int		counter;
	int		size;

	size = ft_lstsize(tmp);
	map = malloc(sizeof(*map) * (size + 1));
	counter = -1;
	while (++counter < size)
	{
		map[counter] = tmp->content;
		tmp = tmp->next;
	}
	map[size] = NULL;
	return (map);
}

void	empty_func(void *ptr)
{
	(void) ptr;
}

int	ft_strrchr_int(char *line, int chr)
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
	int		index;

	index = -1;
	resized_line = NULL;
	arr = map->map;
	while (arr[++index])
	{
		if (ft_strrchr_int_arr(arr[index], WALL_CHARS) < map->map_size.x || !is_wall(arr[index][ft_strlen(arr[index]) - 1]))
		{
			resized_line = malloc(sizeof(char) * (map->map_size.x + 1));
			ft_memset(resized_line, ' ', sizeof(char) * map->map_size.x);
			resized_line[map->map_size.x] = 0;
			ft_memcpy(resized_line, arr[index], ft_strrchr_int_arr(arr[index], WALL_CHARS));
			free(arr[index]);
			arr[index] = resized_line;
		}
	}
}

void	convert_spaces_to_zeros(t_map *map)
{
	char	**arr;
	int		yindex;
	int		xindex;

	yindex = -1;
	arr = map->map;
	while (arr[++yindex])
	{
		xindex = -1;
		while (arr[yindex][++xindex])
			if (arr[yindex][xindex] == ' ')
				arr[yindex][xindex] = '0';
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
	ft_lstclear(&tmp, empty_func);
	map->map_size.x = get_map_width(map->map);
	map->map_size.y = ft_arraylen((void **) map->map);
	map_to_rectangle(map);
	ft_putendl_fd("amogus_gaming", 1);
}

t_map	*free_map(t_map *map)
{
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
		// ft_putendl_fd("amogus_gaming", 1);
		map = create_empty_map();
		get_textures(map, fd);
		get_map(map, fd);
	}
	if (is_enclosed(map))
	{
		convert_spaces_to_zeros(map);
		return (map);
	}
	ft_putendl_fd("Faulty map", 1);
	return (free_map(map));
}
