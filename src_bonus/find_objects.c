#include "../inc_bonus/cub3d_bonus.h"

int	ft_strchr_int(char *line, int chr)
{
	char	*wall;

	wall = ft_strchr(line, chr);
	if (line && wall)
		return (wall - line);
	return (INT32_MAX);
}

int	ft_strchr_int_arr(char *line, char* chr)
{
	int		min;
	int		curr;
	size_t	counter;

	counter = 0;
	min = ft_strchr_int(line, chr[counter]);
	while (++counter < ft_strlen(chr))
	{
		curr = ft_strchr_int(line, chr[counter]);
		if (min > curr)
			min = curr;
	}
	return (min);
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

void	find_enemy(t_list **lst, t_object *object)
{
	t_enemy	*enemy;

	if (object->type == 'e')
	{
		enemy = malloc(sizeof(*enemy));
		ft_bzero(enemy, sizeof(*enemy));
		enemy->object = object;
		enemy->starting_pos = enemy->object->pos;
		enemy->path = NULL;
		enemy->pathfinding_algorithm = pathfinding_algo_straight;
		ft_lstadd_back(lst, ft_lstnew(enemy));
	}
}

void	find_objects(t_map *map)
{
	int			counter;
	int			x_coord;
	char		*line;
	t_object	*object;

	counter = -1;
	while (map->map[++counter])
	{
		x_coord = -1; // not necessary ?
		line = map->map[counter];
		while (ft_strchr_int_arr(line, OBJECT_CHARS) != INT32_MAX)
		{
			object = malloc(sizeof(*object));
			ft_bzero(object, sizeof(*object));
			x_coord = (line - map->map[counter]) + ft_strchr_int_arr(line, OBJECT_CHARS);
			object->pos = (t_fvector) {(float )x_coord + 0.5f,
				(float )counter + 0.5f};
			object->distance = fvector_distance((t_fvector)
				{map->player_coords.x, map->player_coords.y}, object->pos);
			object->type = map->map[counter][x_coord];
			ft_lstadd_back(&map->objects, ft_lstnew(object));
			find_enemy(&map->enemies, object);
			line = map->map[counter] + x_coord + 1;
			// printf("%s\n", line);
			// printf("%d %d\n", counter, x_coord);
		}
	}
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