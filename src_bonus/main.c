#include "../inc_bonus/cub3d_bonus.h"

int main(int ac, char **av)
{
	t_map	*map;

	map = parse_file(ac, av);
	if (map)
	{
//		print_map_debug(map);
		init_game(map);
	}
}
