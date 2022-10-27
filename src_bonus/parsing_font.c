#include "../inc_bonus/cub3d_bonus.h"

void	parse_font(t_map *map, int fd, char **line)
{
	int		index;

	index = -1;
	if (!*line)
		*line = skip_empty_lines(fd);
	while (line && *line && !ft_strncmp(*line, FONT_PREFIX,
			ft_strlen(FONT_PREFIX)))
	{
		index = (*line)[1] - FONT_OFFSET;
		if (0 <= index && index < MAX_FONT_CHARS)
			ft_lstadd_back(&map->font[index].texture,
				ft_lstnew(ft_strdup(*line + 3)));
		free(*line);
		*line = skip_empty_lines(fd);
	}	
}
