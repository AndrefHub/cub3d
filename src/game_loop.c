#include "../inc/cub3d.h"

void	put_frame(t_game *game)
{
	put_image_to_image(&game->hud_img, (t_vector)
	{(game->mlx.win_size.x - game->img.size.x) / 2, 0}, &game->img);
	mlx_put_image_to_window(game->mlx.id, game->mlx.window,
		game->hud_img.mlx_img, 0, 0);
}

int	game_loop(t_scene *scene)
{
	scene->scene_func(scene->parameter);
	return (0);
}
