#include "../inc/cub3d.h"

int	get_map_width(char **map)
{
	int	max_width;

	max_width = 0;
	while (map)
	{
		if (max_width < (int)ft_strlen(*map))
			max_width = ft_strlen(*map);
		++map;
	}
	return (max_width);
}

int	set_player(t_map *map, char *line, char *orient)
{
	int	x;

	x = ft_find_substr(line, orient);
	if (x != -1)
	{
		if (map->player_coords.x == BAD_COORD)
		{
			map->player_coords.x = x;
			map->player_coords.y = ft_arraylen(map->map);
			map->player_orient = *orient;
		}
		else
			return (BAD_COORD);
	}
	return (0);
}

int	find_player(t_map *map, char *line)
{
	int	return_code;

	return_code = set_player(map, line, "N");
	return_code += set_player(map, line, "S");
	return_code += set_player(map, line, "W");
	return_code += set_player(map, line, "E");
	return (return_code);
}

int	check_top_wall(char **map)
{
	int	x;
	int	width;
	// int	last_y;
	int	curr_y;

	x = -1;
	width = get_map_width(map);
	// last_y = get_non_space_index_top(map, x);
	while (++x < width)
	{
		curr_y = get_non_space_index_top(map, x);
		if (curr_y && map[curr_y][x] != '1')
			return (0);
		// last_y = curr_y;
	}
	return (1);
}

int	check_bottom_wall(char **map)
{
	int	x;
	int	width;
	// int	last_y;
	int	curr_y;

	x = -1;
	width = get_map_width(map);
	// last_y = get_non_space_index_top(map, x);
	while (++x < width)
	{
		curr_y = get_non_space_index_top(map, x);
		if (curr_y && map[curr_y][x] != '1')
			return (0);
		// last_y = curr_y;
	}
	return (1);
}

int	check_left_wall(char **map)
{
	int	last_x;
	int	curr_x;

	if (!ft_strchr(*map, '1'))
		return (0);
	last_x = get_non_space_index_left(map);
	while (map[1])
	{
		if (!ft_strchr(map[1], '1'))
			return (0);
		curr_x = get_non_space_index_left(map[1]);
		if (map[1][curr_x] != '1' || (last_x < curr_x
			&& check_longer_row_border(map, last_x, curr_x, 'l')))
			return (0);
		else if (last_x > curr_x && check_longer_row_border(map[1], curr_x, last_x, 'l'))
			return (0);
		last_x = curr_x;
		++map;
	}
	return (1);
}

int	check_right_wall(char **map)
{
	int	last_x;
	int	curr_x;

	if (!ft_strchr(*map, '1'))
		return (0);
	last_x = get_non_space_index_right(*map);
	while (map[1])
	{
		if (!ft_strchr(map[1], '1'))
			return (0);
		curr_x = get_non_space_index_right(map[1]);
		if (map[1][curr_x] != '1' || (last_x > curr_x
			&& check_longer_row_border(*map, last_x, curr_x, 'r')))
			return (0);
		else if (last_x < curr_x && check_longer_row_border(map[1], curr_x, last_x, 'r'))
			return (0);
		last_x = curr_x;
		map = map->next;
	}
	return (1);
}

int	is_enclosed(t_map *args)
{
	return (check_left_wall(args->map) && check_right_wall(args->map)
		&& check_top_wall(args->map) && check_bottom_wall(args->map));
}
