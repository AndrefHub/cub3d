#include "../inc_bonus/cub3d_bonus.h"

float	fvector_distance(t_fvector lhs, t_fvector rhs)
{
	return (sqrtf(powf(lhs.x - rhs.x, 2) + powf(lhs.y - rhs.y, 2)));
}

int	float_sign(float f)
{
	return (1 - (f == 0.) - 2 * (f < 0.));
}
