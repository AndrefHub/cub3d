/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:16 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:47:19 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// t_map	*free_map(t_map *map)
// {
// 	if (map)
// 		ft_freesplit(map->map);
// 	return (NULL);
// }

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
