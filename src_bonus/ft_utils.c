#include "../inc_bonus/cub3d_bonus.h"

int	ft_strchr_int(char *line, int chr)
{
	char	*wall;

	wall = ft_strchr(line, chr);
	if (line && wall)
		return (wall - line);
	return (INT32_MAX);
}

int	ft_arraylen(void **arr)
{
	int	counter;

	counter = 0;
	while (arr && arr[counter])
		++counter;
	return (counter);
}

int	is_space(char c)
{
	return (c != ' ' && c != '\t' && c != '\n');
}

int	is_line_empty(char *line)
{
	while (line && *line)
	{
		if (is_space(*line))
			return (0);
		++line;
	}
	return (1);
}

float	distancef(t_fvector *vector1, t_fvector *vector2)
{
	return (sqrtf(powf(vector2->x - vector1->x, 2)
			+ powf(vector2->y - vector1->y, 2)));
}
