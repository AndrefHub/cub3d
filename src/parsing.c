#include "../inc/cub3d.h"

void	get_textures(t_map *map, int fd)
{
	map->NO = crop_prefix(get_texture(fd), "NO");
	map->SO = crop_prefix(get_texture(fd), "SO");
	map->WE = crop_prefix(get_texture(fd), "WE");
	map->EA = crop_prefix(get_texture(fd), "EA");
	map->F = convert_rgb(crop_prefix(get_texture(fd), "F"));
	map->C = convert_rgb(crop_prefix(get_texture(fd), "C"));
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
		resized_line = arr[index];
		if ((int)ft_strlen(arr[index]) < map->map_size.x)
		{
			resized_line = malloc(sizeof(char) * (map->map_size.x + 1));
			ft_memset(resized_line, '0', sizeof(char) * map->map_size.x);
			resized_line[map->map_size.x] = 0;
			ft_memcpy(resized_line, arr[index], ft_strlen(arr[index]));
			free(arr[index]);
			arr[index] = resized_line;
		}
		while (*resized_line)
		{
			if (*resized_line == ' ')
				*resized_line = '0';
			++resized_line;
		}
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
	// ft_putendl_fd("amogus_gaming", 1);
	map_to_rectangle(map);	
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
	// if (is_enclosed(map))
	// 	return (map);
	// return (free_map(map));
	return (map);
}
