#include "../inc/cub3d.h"

void	draw_texture_set(t_game *game, struct s_column *column)
{
	const char chr = game->grid[column->cell.y][column->cell.x];

	column->texture_id = ft_strchr(WALL_CHARS, chr) - WALL_CHARS;
	//		texture_id = ft_strchr(CARDINAL_POINTS, game->column[x].dir) - CARDINAL_POINTS;
}