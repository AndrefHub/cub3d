#include "../inc/cub3d.h"

void	draw_texture_set(t_game *game, struct s_column *column)
{
	const char chr = game->grid[column->cell.y][column->cell.x];

	ft_putchar(chr);
}