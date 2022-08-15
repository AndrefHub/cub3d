#include "../inc/cub3d.h"

void	set_values_to_vector(t_vector *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
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
