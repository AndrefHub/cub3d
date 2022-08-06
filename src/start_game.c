#include "../inc/cub3d.h"

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
	int	x;
	int	y;

	game->frames++;
	if (!game->init_render)
	{
		game->init_render = 0;
		y = 0;
		while (game->map->map)
		{
			char *line;
			line = game->map->map->content;
			x = 0;
			while (line)
			{
				if (line[x] == '0')

				x++;
			}
			y++;
		}
	}
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->mlx.assets, 0, 0);
	return (0);
}

void	start_mlx(t_game *game)
{
	mlx_loop_hook(game->mlx.id, ft_update, (void *) game);
	mlx_hook(game->mlx.window, 2, 0, key_hook, game);
	mlx_hook(game->mlx.window, 17, 0, close_game, (void *) game);
	mlx_loop(game->mlx.id);
}

int start_game(t_game *game)
{
	start_mlx(game);
	return (0);
}

void	initialize_game(t_game *game)
{
	game->mlx.window = mlx_new_window(game->mlx.id, WIN_WIDTH, WIN_HEIGHT - 54, PROJ_NAME);
	game->init_render = 0;
	game->frames = 0;
	game->size = MAP_GRID_SIZE;
}

void	initialize_sprites(t_game *game)
{
	//
	int *size;

	size = (int *) malloc(sizeof(int));
	*size = 1000;
	game->mlx.assets = mlx_xpm_file_to_image(game->mlx.id, "assets/img.xpm", size, size);
	//

}

int	game(t_map *map)
{
	t_game	game;

	game.map = map;
	game.mlx.id = mlx_init();
	if (!game.mlx.id)
		return (0);
	initialize_game(&game);
	initialize_sprites(&game);
	start_game(&game);
	return (1);
}