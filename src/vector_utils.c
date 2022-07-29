#include "../cub3d.h"

void	set_values_to_vector(t_vector *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
}

t_vector	*get_vector_from_direction(int direction)
{
	t_vector	*vector;

	vector = malloc(sizeof(*vector));
	if (direction % 4 == 0)
		set_values_to_vector(vector, 1, 0);
	else if (direction % 4 == 1)
		set_values_to_vector(vector, 0, -1);
	else if (direction % 4 == 2)
		set_values_to_vector(vector, -1, 0);
	else if (direction % 4 == 3)
		set_values_to_vector(vector, 0, 1);
	// if (direction % 8 == 0)
	// 	set_values_to_vector(vector, 1, 0);
	// else if (direction % 8 == 1)
	// 	set_values_to_vector(vector, 1, -1);
	// else if (direction % 8 == 2)
	// 	set_values_to_vector(vector, 0, -1);
	// else if (direction % 8 == 3)
	// 	set_values_to_vector(vector, -1, -1);
	// else if (direction % 8 == 4)
	// 	set_values_to_vector(vector, -1, 0);
	// else if (direction % 8 == 5)
	// 	set_values_to_vector(vector, -1, 1);
	// else if (direction % 8 == 6)
	// 	set_values_to_vector(vector, 0, 1);
	// else if (direction % 8 == 7)
	// 	set_values_to_vector(vector, 1, 1);
	return (vector);
}

t_vector	*vector_sum(t_vector *lhs, t_vector *rhs)
{
	lhs->x += rhs->x;
	lhs->y += rhs->y;
	printf("\033[1;33mSum X%d Y%d\n", lhs->x, lhs->y);
	return (lhs);
}

int	operator_equals_vector(t_vector *lhs, t_vector *rhs)
{
	return (lhs->x == rhs->x && lhs->y == rhs->y);
}
