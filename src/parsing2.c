#include "../inc/cub3d.h"

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

//void	get_vector_from_direction(t_vector *vector, int direction)
//{
//
//}
//
//int	recursive_enclosure_checker(t_vector starting, t_vector last, t_vector prelast)
//{
//	static int	recursion_depth = 0;
//
//	if (++recursion_depth > 1000)
//		return (0);
//
//}
//
//int	is_enclosed(t_map *args)
//{
//	t_list	*map;
//	char	*line;
//	int		x;
//
//	map = args->map;
//	x = args->player_coords.x;
//	line = ft_lstat(map, args->player_coords.y);
//	while (line[x] != '1')
//		--x;
//
//}
