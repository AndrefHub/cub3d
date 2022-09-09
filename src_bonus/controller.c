#include "../inc_bonus/cub3d_bonus.h"
#include <unistd.h>

void	open_door(t_game *game)
{
	const int	x = (int)game->player.pos.x / MAP_GRID_SIZE;
	const int	y = (int)game->player.pos.y / MAP_GRID_SIZE;
	const float	angle = game->player.angle;
	char		*to_change;
	
	to_change = NULL;
	if (PI / 4 <= angle && angle <= 3 * PI / 4 && ft_tolower(game->grid
		[y + 1][x]) == 'd')
		to_change = game->grid[y + 1] + x;
	else if (3 * PI / 4 <= angle && angle <= 5 * PI / 4 && ft_tolower(game->grid
		[y][x - 1]) == 'd')
		to_change = game->grid[y] + x - 1;
	else if (5 * PI / 4 <= angle && angle <= 7 * PI / 4 && ft_tolower(game->grid
		[y - 1][x]) == 'd')
		to_change = game->grid[y - 1] + x;
	else if ((7 * PI / 4 <= angle || angle <= PI / 4) && ft_tolower(game->grid
		[y][x + 1]) == 'd')
		to_change = game->grid[y] + x + 1;
	if (to_change && *to_change == 'd')
		*to_change = 'D';
	else if (to_change && *to_change == 'D')
		*to_change = 'd';
}

void	change_textures(t_game *game)
{
	static int clocks_per_frame = 1000 / FRAMERATE;
	int	index;
	int	counter;
	int frames_to_move;
	static int s = 0;

	frames_to_move = (get_time() - game->time.startup) / clocks_per_frame \
		- (game->time.last - game->time.startup) / clocks_per_frame;
	if (frames_to_move)
	{
		index = -1;
		while (++index < MAX_WALL_CHARS)
		{
			counter = -1;
			while (++counter < frames_to_move)
				game->map->walls[index].img = game->map->walls[index].img->next;
			game->textures[index] = *(t_img *)game->map->walls[index].img->content;	
		}
	}
	++s;
}

void	enemy_attack(t_game *game)
{
	(void)game;
	ft_putendl_fd("Enemy attacked you", 1);
}

void	enemy_move(t_game *game)
{
	// const float	x_dis = game;
	
	if (fvector_distance(game->player.pos, ((t_enemy *)game->map->enemies->content)->pos) < MAP_GRID_SIZE)
		enemy_attack(game);
}
