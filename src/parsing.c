#include "../cub3d.h"

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

void	get_map(t_map *map, int fd)
{
	char	*line;
	t_list	*tmp;

	tmp = NULL;
	line = skip_empty_lines(fd);
	while (line && !ft_is_empty(line))
	{
		ft_lstadd_back(&tmp, ft_lstnew(line));
		find_player(map, line);
		line = skip_empty_lines(fd);
	}
	free(line);
	map->rename_this_to_map = lst_to_char_ptr(tmp);
	ft_lstclear(&tmp, empty_func);
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
	return (map);
}
