#include "../cub3d.h"

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

int	border(t_list *map, t_vector *vector)
{
	char	*line;

	if (ft_lstat(map, vector->y))
		line = ft_lstat(map, vector->y)->content;
	return (line && (int)ft_strlen(line) >= vector->x && line[(int)vector->x] == '1');
}

int	check_longer_row_border(char *shorter, int sindex, int lindex)
{
	while (shorter[sindex] == '1' && sindex <= lindex)
		++sindex;
	return (sindex > lindex);
}

int	check_left_right_walls(t_list *map)
{
	int	last_x;
	int	curr_x;

	if (!ft_strchr(map->content, '1'))
		return (0);
	last_x = ft_strchr(map->content, '1') - (char *)map->content;
	while (map->next)
	{
		if (!ft_strchr(map->next->content, '1'))
			return (0);
		curr_x = ft_strchr(map->next->content, '1') - (char *)map->next->content;
		if (last_x < curr_x && check_longer_row_border(map->content, last_x, curr_x))
			return (0);
		else if (last_x > curr_x && check_longer_row_border(map->next->content, curr_x, last_x))
			return (0);
		map = map->next;
	}
	return (1);
}

int	is_enclosed(t_map *args)
{
	return (check_left_right_walls(args->map));
}
