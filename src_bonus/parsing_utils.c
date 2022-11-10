/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:18 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:50:20 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	check_assets(t_map *map)
{
	int	counter;

	counter = -1;
	while (++counter < MAX_WALL_CHARS)
		if (!map->walls[counter].texture)
			error_exit(NULL, 1, "Parsing fail: \
Invalid entries order or missing wall texture filename");
	counter = -1;
	while (++counter < MAX_OBJECTS)
		if (!map->object[counter].texture)
			error_exit(NULL, 1, "Parsing fail: \
Invalid entries order or missing wall texture filename");
	counter = -1;
	while (++counter < MAX_SOUNDS)
		if (!map->sounds[counter])
			error_exit(NULL, 1, "Parsing fail: \
Invalid entries order or missing sound filename");
	if (!map->floor.texture)
		error_exit(NULL, 1, "Parsing fail: \
Invalid entries order or missing floor texture filename");
	if (!map->ceiling.texture)
		error_exit(NULL, 1, "Parsing fail: \
Invalid entries order or missing ceiling texture filename");
	return (1);
}

int	ft_strrchr_int(const char *line, int chr)
{
	char	*wall;

	wall = ft_strrchr(line, chr);
	if (line && wall)
		return (wall - line + 1);
	return (-1);
}

int	ft_strrchr_int_arr(const char *line, char *chr)
{
	int		max;
	int		curr;
	size_t	counter;

	counter = 0;
	max = ft_strrchr_int(line, chr[counter]);
	while (++counter < ft_strlen(chr))
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
	char	*resized;
	int		i;

	i = -1;
	resized = NULL;
	arr = map->map;
	while (arr[++i])
	{
		if (ft_strrchr_int_arr(arr[i], WALL_CHARS) < 0)
			error_exit(NULL, 1, "Parsing error: assets incorrect order \
			or line without walls");
		if (ft_strrchr_int_arr(arr[i], WALL_CHARS) < map->map_size.x
			|| !is_wall(arr[i][ft_strlen(arr[i]) - 1]))
		{
			resized = malloc(sizeof(char) * (map->map_size.x + 1));
			if (resized == NULL)
				error_exit(NULL, 1, "Memory allocation error: Map processing");
			ft_memset(resized, ' ', sizeof(char) * map->map_size.x);
			resized[map->map_size.x] = 0;
			ft_memcpy(resized, arr[i], ft_strrchr_int_arr(arr[i], WALL_CHARS));
			free(arr[i]);
			arr[i] = resized;
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
