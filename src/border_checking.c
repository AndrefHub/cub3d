#include "../cub3d.h"

int	set_player(t_map *map, char *line, char *orient)
{
	int	x;

	x = ft_find_substr(line, orient);
	if (x != -1)
	{
		if (map->player_coords.x == BAD_COORD)
		{
			map->player_coords.x = x;
			map->player_coords.y = ft_lstsize(map->map);
			map->player_orient = orient[0];
		}
		else
			return (BAD_COORD);
	}
	return (0);
}

int	find_player(t_map *map, char *line)
{
	int	return_code;

	return_code = set_player(map, line, "N");
	return_code += set_player(map, line, "S");
	return_code += set_player(map, line, "W");
	return_code += set_player(map, line, "E");
	return (return_code);
}

void	set_values_to_vector(t_vector *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
}

void	rotate_vector_counterclockwise(t_vector *vector)
{
	int	temp;

	temp = vector->x;
	vector->x = -vector->y;
	vector->y = temp;
}

t_vector	*get_vector_from_direction(int direction)
{
	t_vector	*vector;

	vector = malloc(sizeof(*vector));
	if (direction % 8 == 0)
		set_values_to_vector(vector, 1, 0);
	else if (direction % 8 == 1)
		set_values_to_vector(vector, 1, 1);
	else if (direction % 8 == 2)
		set_values_to_vector(vector, 0, 1);
	else if (direction % 8 == 3)
		set_values_to_vector(vector, -1, 1);
	else if (direction % 8 == 4)
		set_values_to_vector(vector, -1, 0);
	else if (direction % 8 == 5)
		set_values_to_vector(vector, -1, -1);
	else if (direction % 8 == 6)
		set_values_to_vector(vector, 0, -1);
	else if (direction % 8 == 7)
		set_values_to_vector(vector, 1, -1);
	return (vector);
}

t_vector	*vector_sum(t_vector *lhs, t_vector *rhs)
{
	lhs->x += rhs->x;
	lhs->y += rhs->y;
	return (lhs);
}

int	border(t_list *map, t_vector *vector)
{
	char	*line;

	line = ft_lstat(map, vector->y)->content;
	return (line && (int)ft_strlen(line) > vector->x && line[(int)vector->x] == '1');
}

int	operator_equals_vector(t_vector *lhs, t_vector *rhs)
{
	return (lhs->x == rhs->x && lhs->y == rhs->y);
}

int	recursive_enclosure_checker(t_list *map, t_vector* starting, t_vector* last, int direction)
{
	static int	recursion_depth = 0;
	t_vector	*check;
	int			counter;

	if (++recursion_depth > 1000)
		return (0);
	if (operator_equals_vector(starting, last))
	{
		free(last);
		return (1);
	}
	counter = -1;
	while (++counter < 8)
	{
		check = vector_sum(get_vector_from_direction(direction + counter - 2), last);
		if (border(map, check))
		{
			free(last);
			return (recursive_enclosure_checker(map, starting, check, (direction + counter - 2) % 8));
		}
		free(check);
	}
	return (0);
}

int	is_enclosed(t_map *args)
{
	char		*line;
	t_vector	vec;
	int			ret_val;

	vec.x = args->player_coords.x;
	vec.y = args->player_coords.y;
	line = ft_lstat(args->map, args->player_coords.y)->content;
	while (--(vec.x) >= 0)
	{
		if (line[vec.x] == '1')
		{
			ret_val = recursive_enclosure_checker(args->map, &vec, vector_sum(get_vector_from_direction(6), &vec), 6);
			if (ret_val)
				return (ret_val);
		}
	}
	return (0);
}
