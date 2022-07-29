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
	map->player_coords.x = BAD_COORD;
	map->player_coords.y = BAD_COORD;
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

int		ft_is_empty(char *line)
{
	while (line && *line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		++line;
	}
	return (1);
}

void	print_map_debug(t_map *map)
{
	t_list	*lst;

	printf("NO %s\nSO %s\nWE %s\nEA %s\nF %d,%d,%d\nC %d,%d,%d\n\n", map->NO, map->SO, map->WE, map->EA,
		map->F >> 16, (map->F >> 8) % (1 << 8), map->F % (1 << 8),
		map->C >> 16, (map->C >> 8) % (1 << 8), map->C % (1 << 8));
	// printf("%lu %lu\n", map->map->size, map->map->capacity);
	printf("Player X: %d\nPlayer Y: %d\nPlayer orientation: %c\n", map->player_coords.x, map->player_coords.y, map->player_orient);
	lst = map->map;
	while (lst)
	{
		printf("%s", (char *)lst->content);
		lst = lst->next;
	}
	printf("Is enclosed? %d", is_enclosed(map));
}