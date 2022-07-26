#include "../cub3d.h"

t_map	*create_empty_map()
{
	t_map	*map;

	map = malloc(sizeof(*map));
	map->map = NULL;
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
	map->EA = NULL;
	map->C = 0;
	map->F = 0;
	return (map);
}

int	ft_arraylen(void **arr)
{
	int	counter;

	counter = 0;
	while (arr[counter] != NULL)
		++counter;
	return (counter);
}