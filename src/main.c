#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_map	*map;

	map = parse_file(ac, av);
	if (map)
	{
		init_game(map);
	}
}