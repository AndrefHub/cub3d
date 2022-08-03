#include "../cub3d.h"

int	get_map_width(t_list *map)
{
	int	max_width;

	max_width = 0;
	while (map)
	{
		if (max_width < (int)ft_strlen(map->content))
			max_width = ft_strlen(map->content);
		map = map->next;
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
			map->player_coords.y = ft_lstsize(map->map);
			map->player_orient = orient[0];
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

int	check_top_wall(t_list *map)
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
		if (curr_y && ((char *)ft_lstat(map, curr_y)->content)[x] != '1')
			return (0);
		// last_y = curr_y;
	}
	return (1);
}

int	check_bottom_wall(t_list *map)
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
		if (curr_y && ((char *)ft_lstat(map, curr_y)->content)[x] != '1')
			return (0);
		// last_y = curr_y;
	}
	return (1);
}

int	check_left_wall(t_list *map)
{
	int	last_x;
	int	curr_x;

	if (!ft_strchr(map->content, '1'))
		return (0);
	last_x = get_non_space_index_left(map->content);
	while (map->next)
	{
		if (!ft_strchr(map->next->content, '1'))
			return (0);
		curr_x = get_non_space_index_left(map->next->content);
		if (((char *)map->next->content)[curr_x] != '1' || (last_x < curr_x
			&& check_longer_row_border(map->content, last_x, curr_x, 'l')))
			return (0);
		else if (last_x > curr_x && check_longer_row_border(map->next->content, curr_x, last_x, 'l'))
			return (0);
		last_x = curr_x;
		map = map->next;
	}
	return (1);
}

int	check_right_wall(t_list *map)
{
	int	last_x;
	int	curr_x;

	if (!ft_strchr(map->content, '1'))
		return (0);
	last_x = get_non_space_index_right(map->content);
	while (map->next)
	{
		if (!ft_strchr(map->next->content, '1'))
			return (0);
		curr_x = get_non_space_index_right(map->next->content);
		if (((char *)map->next->content)[curr_x] != '1' || (last_x > curr_x
			&& check_longer_row_border(map->content, last_x, curr_x, 'r')))
			return (0);
		else if (last_x < curr_x && check_longer_row_border(map->next->content, curr_x, last_x, 'r'))
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
