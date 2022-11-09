#include "../inc/cub3d.h"

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

char	*parse_texture(int fd, char **line, char *prefix)
{
	if (!*line)
		*line = skip_empty_lines(fd);
	if (!(line && *line && !ft_strncmp(*line, prefix,
				ft_strlen(prefix))))
		return (NULL);
	*line = NULL;
	return (crop_prefix(*line, prefix));
}

void	parse_assets(t_map *map, int fd)
{
	int		counter;
	char	*line;

	line = NULL;
	counter = -1;
	map->walls[0].texture = 
	// parse_texture(fd, &line, (t_parse_info){NULL, "F", &map->floor, 0});
	// parse_texture(fd, &line, (t_parse_info){NULL, "C", &map->ceiling, 0});
}
