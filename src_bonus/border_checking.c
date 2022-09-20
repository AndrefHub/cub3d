#include "../inc_bonus/cub3d_bonus.h"

int	get_map_width(const char **map)
{
	int	max_width;

	max_width = 0;
	while (*map)
	{
		ft_putendl_fd(*map, 1);
		if (max_width < ft_strrchr_int_arr(*map, WALL_CHARS))
			max_width = ft_strrchr_int_arr(*map, WALL_CHARS);
		++map;
	}
	return (max_width);
}

int	is_wall(char c)
{
	return (ft_strchr(WALL_CHARS, c) != NULL);
}

int	is_enemy(char c)
{
	return (ft_strchr(ENEMY_CHARS, c) != NULL);
}

int	check_enclosure(t_map *map, t_vector vec)
{
	if (map->map[vec.y][vec.x] == ' ' || is_wall(map->map[vec.y][vec.x]))
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

int	is_map_enclosed(t_map *args)
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
