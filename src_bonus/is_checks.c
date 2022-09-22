#include "../inc_bonus/cub3d_bonus.h"

int	is_wall(char c)
{
	return (ft_strchr(WALL_CHARS, c) != NULL);
}

int	is_enemy(char c)
{
	return (ft_strchr(ENEMY_CHARS, c) != NULL);
}

int	is_edible(char c)
{
	return (ft_strchr(EDIBLE_CHARS, c) != NULL);
}

int	is_object(char c)
{
	return (is_edible(c) || is_enemy(c));
}