#include "../inc/cub3d_bonus.h"

void	get_textures(t_map *map, int fd)
{
	char	*line;

	line = NULL;
	get_textures_in_lists(map, fd, &line);
	map->F = convert_rgb(crop_prefix(line, 'F'));
	map->C = convert_rgb(crop_prefix(get_texture(fd), 'C'));
}

int	is_prefix_number(t_map *map, char *line)
{
	return (line && is_wall(*line) && ft_atoi(line + 1) == ft_lstsize(map->texture_list[(int )(*line - '1')]));
}

void	get_textures_in_lists(t_map *map, int fd, char **line)
{
	if (is_prefix_number(map, *line))
	{
		ft_lstadd_back(&map->texture_list[(int )(**line - '1')], ft_lstnew(crop_prefix(*line, **line)));
	}
	*line = get_texture(fd);
	while (is_prefix_number(map, *line))
	{
		ft_lstadd_back(&map->texture_list[(int )(**line - '1')], ft_lstnew(crop_prefix(*line, **line)));
		*line = get_texture(fd);
	}
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
	char	*one;

	one = ft_strrchr(line, chr);
	if (line)
		return (one - line + 1);
	return (-1);
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
		if (ft_strrchr_int(arr[index], '1') < map->map_size.x || arr[index][ft_strlen(arr[index]) - 1] != '1')
		{
			resized_line = malloc(sizeof(char) * (map->map_size.x + 1));
			ft_memset(resized_line, ' ', sizeof(char) * map->map_size.x);
			resized_line[map->map_size.x] = 0;
			ft_memcpy(resized_line, arr[index], ft_strrchr_int(arr[index], '1'));
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
	// ft_putendl_fd("amogus_gaming", 1);
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
	// char	*line;

	map = NULL;
	fd = check_file(ac, av);
	if (fd != BAD_FILE)
	{
		map = create_empty_map();
		get_textures(map, fd);
		get_map(map, fd);
	}
	if (is_enclosed(map))
	{
		convert_spaces_to_zeros(map);
		return (map);
	}
	ft_putendl_fd("amogus_gaming2", 1);
	return (free_map(map));
}
