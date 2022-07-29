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

void	get_map(t_map *map, int fd)
{
	char	*line;

	line = skip_empty_lines(fd);
	while (line && !ft_is_empty(line))
	{
		ft_lstadd_back(&map->map, ft_lstnew(line));
		find_player(map, line);
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
