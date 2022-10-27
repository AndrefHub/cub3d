#include "../inc_bonus/cub3d_bonus.h"

char	*crop_prefix(char *line, char *prefix)
{
	char	*new_line;
	char	*begin;

	if (!line || ft_strncmp(line, prefix, ft_strlen(prefix)))
	{
		free(line);
		return (NULL);
	}
	begin = line + ft_strlen(prefix);
	while (get_string_index(WALL_CHARS, *begin) != -1)
		++begin;
	while (*begin == ' ' || *begin == '\t')
		++begin;
	new_line = ft_strdup(begin);
	free(line);
	return (new_line);
}

char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && is_line_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = 0;
	return (line);
}

int	convert_to_rgb(char *line)
{
	char	**rgb_values;
	int		rgb;

	rgb = BAD_COLOUR;
	rgb_values = ft_split(line, ',');
	if (ft_arraylen((void **)rgb_values) == 3)
		rgb = (ft_atoi(rgb_values[0]) << 16) + (ft_atoi(rgb_values[1]) << 8)
			+ ft_atoi(rgb_values[2]);
	ft_freesplit(rgb_values);
	free(line);
	return (rgb);
}

char	*ft_strcat_delim(char *first, char delim, char *second)
{
	char	*dup;
	size_t	flen;
	size_t	slen;
	int		fcounter;
	int		scounter;

	fcounter = -1;
	scounter = -1;
	flen = ft_strlen(first);
	slen = ft_strlen(second);
	dup = (char *)malloc(sizeof(char) * (flen + 1 + slen + 1));
	if (!dup)
		return (NULL);
	while (first[++fcounter])
		dup[fcounter] = first[fcounter];
	dup[fcounter++] = delim;
	while (second[++scounter])
		dup[fcounter + scounter] = second[scounter];
	dup[fcounter + scounter] = '\0';
	return (dup);
}
