#include "../cub3d.h"

int	check_file(int ac, char **av)
{
	int fd;

	if (ac != 2)
		return (BAD_FILE);
	if (ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".cub", 4) != 0)
		return (BAD_FILE);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (BAD_FILE);
	return (fd);
}

char	*crop_prefix(char* line, char *prefix)
{
	char	*new_line;
	char	*begin;

	if (ft_strncmp(line, prefix, ft_strlen(prefix)))
	{
		free(line);
		return (NULL);
	}
	begin = line + ft_strlen(prefix);
	while (*begin == ' ' || *begin == '\t')
		++begin;
	// if (*begin == '.' && *(begin + 1) == '/')
	new_line = ft_strdup(begin);
	free(line);
	return (new_line);
}

int		ft_is_empty(char *line)
{
	while (line && *line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		++line;
	}
	return (1);
}

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (ft_is_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

char	*get_texture(int fd)
{
	return (skip_empty_lines(fd));
}

int convert_rgb(char *line)
{
	char	**rgb_values;
	int		rgb;

	rgb = BAD_COLOUR;
	rgb_values = ft_split(line, ',');
	if (ft_arraylen((void **)rgb_values) == 3)
		rgb = ft_atoi(rgb_values[0]) * (1 << 16) + ft_atoi(rgb_values[1]) *
			(1 << 8) + ft_atoi(rgb_values[2]);
	ft_freesplit(rgb_values);
	return (rgb);
}

void	get_textures(t_map *map, int fd)
{
	map->NO = crop_prefix(get_texture(fd), "NO");
	map->SO = crop_prefix(get_texture(fd), "SO");
	map->WE = crop_prefix(get_texture(fd), "WE");
	map->EA = crop_prefix(get_texture(fd), "EA");
	map->F = convert_rgb(crop_prefix(get_texture(fd), "F"));
	map->C = convert_rgb(crop_prefix(get_texture(fd), "C"));
}

void	get_map(t_map *map, int fd)
{
	char	*line;

	// map->map = vector_init_default();
	line = skip_empty_lines(fd);
	while (line && !ft_is_empty(line))
	{
		ft_lstadd_back(&map->map, ft_lstnew(line));
		// vector_push_back(map->map, line);
		line = get_next_line(fd);
	}
	free(line);
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

void	print_map_debug(t_map *map)
{
	t_list	*lst;

	printf("NO %s\nSO %s\nWE %s\nEA %s\nF %d,%d,%d\nC %d,%d,%d\n\n", map->NO, map->SO, map->WE, map->EA,
		map->F >> 16, (map->F >> 8) % (1 << 8), map->F % (1 << 8),
		map->C >> 16, (map->C >> 8) % (1 << 8), map->C % (1 << 8));
	// printf("%lu %lu\n", map->map->size, map->map->capacity);
	lst = map->map;
	while (lst)
	{
		printf("%s", (char *)lst->content);
		lst = lst->next;
	}
}

// int	is_enclosed(t_map *args)
// {
// 	t_list	*map;

// 	map = args->map;
// 	// while ()
// }

int main(int ac, char **av)
{
	t_map	*map;

	printf("%d %d %d %d %d %d %d\n",
		ft_is_empty(""),
		ft_is_empty("    "),
		ft_is_empty("	"),
		ft_is_empty("    \n"),
		ft_is_empty("\n"),
		ft_is_empty(" lOl"),
		ft_is_empty("lOl")
	);
	map = parse_file(ac, av);
	if (map)
	{
		print_map_debug(map);
	}
}