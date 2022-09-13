#include "../inc_bonus/cub3d_bonus.h"

t_map	*free_map(t_map *map)
{
	if (map)
		ft_freesplit(map->map);
	return (NULL);
}

int	ft_strrchr_int(const char *line, int chr)
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
	int		i;

	i = -1;
	resized_line = NULL;
	arr = map->map;
	while (arr[++i])
	{
		if (ft_strrchr_int_arr(arr[i], WALL_CHARS) < 0)
			error_exit(NULL, 1, "Parsing error: assets incorrect order or line without walls");
		if (ft_strrchr_int_arr(arr[i], WALL_CHARS) < map->map_size.x
			|| !is_wall(arr[i][ft_strlen(arr[i]) - 1]))
		{
			resized_line = malloc(sizeof(char) * (map->map_size.x + 1));
			if (resized_line == NULL)
				error_exit(NULL, 1, "Memory allocation error: Map processing");
			ft_memset(resized_line, ' ', sizeof(char) * map->map_size.x);
			resized_line[map->map_size.x] = 0;
			ft_memcpy(resized_line, arr[i], ft_strrchr_int_arr(arr[i], WALL_CHARS));
			free(arr[i]);
			arr[i] = resized_line;
		}
	}
}

void	convert_spaces_to_zeros(t_map *map)
{
	char	**arr;
	int		y;
	int		x;

	y = -1;
	arr = map->map;
	while (arr[++y])
	{
		x = -1;
		while (arr[y][++x])
			if (arr[y][x] == ' ')
				arr[y][x] = '0';
	}
}