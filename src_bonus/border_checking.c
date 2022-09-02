#include "../inc/cub3d_bonus.h"

int	get_map_width(char **map)
{
	int	max_width;

	max_width = 0;
	while (*map)
	{
		ft_putendl_fd(*map, 1);
		if (max_width < ft_strrchr_int(*map, '1'))
			max_width = ft_strrchr_int(*map, '1');
		++map;
	}
	return (max_width);
}

int	set_player(t_map *map, t_list *lst, char *line, char *orient)
{
	int	x;

	x = ft_find_substr(line, orient);
	if (x != -1)
	{
		if (map->player_coords.x == BAD_COORD)
		{
			map->player_coords.x = x;
			map->player_coords.y = ft_lstsize(lst);
			if (*orient == 'E')
				map->player_orient = 0;
			if (*orient == 'N')
				map->player_orient = PI / 2;
			if (*orient == 'W')
				map->player_orient = PI;
			if (*orient == 'S')
				map->player_orient = 3 * PI / 2;
		}
		else
			return (BAD_COORD);
	}
	return (0);
}

int	find_player(t_map *map, char *line, t_list *lst)
{
	int	return_code;

	return_code = set_player(map, lst, line, "N");
	return_code += set_player(map, lst, line, "S");
	return_code += set_player(map, lst, line, "W");
	return_code += set_player(map, lst, line, "E");
	return (return_code);
}

int	is_wall(char c)
{
	return (ft_strrchr_int(WALL_CHARS, c) != -1);
}

int check_enclosure(t_map *map, t_vector vec)
{
	if (map->map[vec.y][vec.x] == ' ' || is_wall(map->map[vec.y][vec.x]))
		return (0);
	if (vec.x == 0 || vec.x == map->map_size.x - 1 || vec.y == 0
		|| vec.y == map->map_size.y - 1)
		return (1);
	return (map->map[vec.y - 1][vec.x] == ' '
		|| map->map[vec.y + 1][vec.x] == ' '
		|| map->map[vec.y][vec.x - 1] == ' '
		|| map->map[vec.y][vec.x + 1] == ' ');
}

int	is_enclosed(t_map *args)
{
	t_vector	check;

	check.y = 0;
	while (check.y < args->map_size.y)
	{
		check.x = 0;
		while (check.x < args->map_size.x)
		{
			if (check_enclosure(args, check))
			{
				return (0);
			}
			++check.x;
		}
		++check.y;
	}
	return (1);
}
