#include "../inc/cub3d.h"

typedef struct mlx_params
{
	void	*id;
	void	*window;
	void	*assets;
}	t_mlx_params;

typedef struct game
{
	t_mlx_params	mlx;
}	t_game;

int	close_game(t_game *game)
{
	mlx_clear_window(game->mlx.id, game->mlx.window);
	mlx_destroy_window(game->mlx.id, game->mlx.window);
	exit(0);
	return (0);
}

int	key_hook(int key, t_game *game)
{
	if (key == ESC_KEY)
		close_game(game);
	return (0);
}

int	ft_update(t_game *game)
{
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->mlx.assets, 0, 0);
	return (0);
}

int ft_new_game(t_game *game)
{
	int	*size;

	size = (int *) malloc(sizeof(int));
	*size = 1000;

	game->mlx.assets = mlx_xpm_file_to_image(game->mlx.id, "assets/img.xpm", size, size);
	ft_putendl_fd("asd", 1);


	mlx_loop_hook(game->mlx.id, ft_update, (void *) game);
	mlx_hook(game->mlx.window, 2, 0, key_hook, game);
	mlx_hook(game->mlx.window, 17, 0, close_game, (void *) game);
	mlx_loop(game->mlx.id);
	return (0);
}

int	init_game(void)
{
	t_game	game;

	game.mlx.id = mlx_init();
	if (!game.mlx.id)
		return (0);
	game.mlx.window = mlx_new_window(game.mlx.id, 2560, 1340, PROJ_NAME);
	ft_new_game(&game);
	return (1);
}