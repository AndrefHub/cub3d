#include "../inc/cub3d_bonus.h"

char	*crop_prefix(char* line, char prefix)
{
	char	*new_line;
	char	*begin;

	if (*line != prefix)
	{
		free(line);
		return (NULL);
	}
	begin = line + 1;
	while ((ft_isdigit(*begin)))
		++begin;
	while (*begin == ' ' || *begin == '\t')
		++begin;
	// if (*begin == '.' && *(begin + 1) == '/')
	new_line = ft_strdup(begin);
	free(line);
	return (new_line);
}

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && ft_is_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = 0;
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
		rgb = (ft_atoi(rgb_values[0]) << 16) + (ft_atoi(rgb_values[1]) << 8)
			+ ft_atoi(rgb_values[2]);
	ft_freesplit(rgb_values);
	return (rgb);
}