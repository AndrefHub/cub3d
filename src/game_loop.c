#include "../inc/cub3d.h"

void	put_frame(t_game *game)
{
	mlx_put_image_to_window(game->mlx.id, game->mlx.window,
		game->img.mlx_img, 0, 0);
}

int	game_loop(t_scene *scene)
{
	scene->scene_func(scene->parameter);
	return (0);
}
