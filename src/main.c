#include "../cub3d.h"

// int	is_enclosed(t_map *args)
// {
// 	t_list	*map;

// 	map = args->map;
// 	// while ()
// }

int main(int ac, char **av)
{
	t_map	*map;

	map = parse_file(ac, av);
	if (map)
	{
		print_map_debug(map);
	}
}