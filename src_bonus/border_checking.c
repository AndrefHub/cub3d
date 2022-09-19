#include "../inc_bonus/cub3d_bonus.h"

int	get_map_width(const char **map)
{
	int	max_width;

	max_width = 0;
	while (*map)
	{
//		ft_putendl_fd(*map, 1);
		if (max_width < ft_strrchr_int(*map, '1'))
			max_width = ft_strrchr_int(*map, '1'); // change wall to WALL_CHARS
		++map;
	}
	return (max_width);
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

// void	find_enemy(t_map *map)
// {
// 	int		counter;
// 	int		x_coord;
// 	char	*line;
// 	t_enemy	*enemy;

// 	counter = -1;
// 	enemy = NULL;
// 	while (map->map[++counter])
// 	{
// 		x_coord = -1;
// 		line = map->map[counter];
// 		while (ft_strchr(line, 'e'))
// 		{
// 			enemy = malloc(sizeof(*enemy));
// 			x_coord = ft_strchr(line, 'e') - map->map[counter];
// 			enemy->object.pos = (t_fvector) {(float )x_coord + 0.5f,
// 				(float )counter + 0.5f};
// 			// enemy->sprite = NULL;
// 			ft_lstadd_back(&map->enemies, ft_lstnew(enemy));
// 			enemy->object.distance = sqrtf(powf((map->player_coords.x + 0.5f)
// 					- (enemy->object.pos.x + 0.5f), 2)
// 					+ powf((map->player_coords.y + 0.5f)
// 					- (enemy->object.pos.y + 0.5f), 2));
// 			ft_lstadd_back(&map->objects, ft_lstnew(&enemy->object));
// 			line += (ft_strchr(line, 'e') - line) + 1;
// 		}
// 	}
// }

void	find_objects(t_map *map)
{
	int			counter;
	int			x_coord;
	char		*line;
	t_object	*object;
	t_enemy		*enemy;

	counter = -1;
	object = NULL; // don't think it's necessary
	while (map->map[++counter])
	{
		x_coord = -1;
		line = map->map[counter];
		while (ft_strrchr_int_arr(line, OBJECT_CHARS) != -1)
		{
			object = malloc(sizeof(*object));
			ft_bzero(object, sizeof(*object));
			x_coord = ft_strrchr_int_arr(line, OBJECT_CHARS);
			object->pos = (t_fvector) {(float )x_coord + 0.5f,
				(float )counter + 0.5f};
			object->distance = sqrtf(powf((map->player_coords.x + 0.5f)
					- (object->pos.x + 0.5f), 2)
					+ powf((map->player_coords.y + 0.5f)
					- (object->pos.y + 0.5f), 2));
			ft_lstadd_back(&map->objects, ft_lstnew(object));
			if (line[x_coord - 1] == 'e')
			{
				enemy = malloc(sizeof(*enemy));
				ft_bzero(enemy, sizeof(*enemy));
				enemy->object = object;
				ft_lstadd_back(&map->enemies, ft_lstnew(enemy));
			}
			line[x_coord - 1] = '0';
//			printf("%d, %d.", counter, x_coord);
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

int	is_wall(char c)
{
	return (ft_strchr(WALL_CHARS, c) != NULL);
}

int check_enclosure(t_map *map, t_vector vec)
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
		return 1;
	return 0;
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
