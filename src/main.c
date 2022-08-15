#include "../inc/cub3d.h"

int	game(t_map *map);

void	init_sound(t_map *map)
{

	cs_context_t	*ctx = cs_make_context(0, 44100, 4096, 2, NULL);
	cs_spawn_mix_thread(ctx);
}

int main(int ac, char **av)
{
	t_map	*map;

	map = parse_file(ac, av);
	if (map)
	{
		init_sound(map);
		print_map_debug(map);
		(void ) ac;
		(void ) av;
		game(map);
	}

}