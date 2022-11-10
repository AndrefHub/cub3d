/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:46:27 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 17:03:10 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

char	*skip_empty_chars(char *line)
{
	while (is_space(*line))
		++line;
	return (line);
}

int	get_map_width(const char **map)
{
	int	max_width;

	max_width = 0;
	while (*map)
	{
		if (max_width < ft_strrchr_int_arr(*map, WALL_CHARS))
			max_width = ft_strrchr_int_arr(*map, WALL_CHARS);
		++map;
	}
	return (max_width);
}

int	check_enclosure(t_map *map, t_vector vec)
{
	if (map->map[vec.y][vec.x] == ' '
		|| (is_wall(map->map[vec.y][vec.x]) && map->map[vec.y][vec.x] != 'D'))
		return (0);
	if (vec.x == 0 || vec.x == map->map_size.x - 1 || vec.y == 0
		|| vec.y == map->map_size.y - 1)
		return (1);
	if (map->map[vec.y - 1][vec.x] == ' '
		|| map->map[vec.y + 1][vec.x] == ' '
		|| map->map[vec.y][vec.x - 1] == ' '
		|| map->map[vec.y][vec.x + 1] == ' ')
		return (1);
	return (0);
}

int	is_map_enclosed(t_map *map)
{
	t_vector	check;

	if (is_wall(*skip_empty_chars(map->map[0])))
		error_exit(NULL, 1, "Invalid entries order or map not enclosed");
	check.y = 0;
	while (check.y < map->map_size.y)
	{
		check.x = 0;
		while (check.x < map->map_size.x)
		{
			if (check_enclosure(map, check))
			{
				return (0);
			}
			++check.x;
		}
		++check.y;
	}
	return (1);
}
