#include "../inc/cub3d.h"

int	game(t_map *map);

int main(int ac, char **av)
{
	t_map	*map;

	map = parse_file(ac, av);
	if (map)
	{
		print_map_debug(map);
		(void ) ac;
		(void ) av;
		game(map);
	}

}