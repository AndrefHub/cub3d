#include "../inc/cub3d.h"

int	is_wall(char c)
{
	return (c == '1');
	// return (ft_strchr(WALL_CHARS, c) != NULL);
}
