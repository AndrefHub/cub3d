#include "../inc_bonus/cub3d_bonus.h"

t_map	*create_empty_map(void)
{
	t_map	*map;

	map = malloc(sizeof(*map));
	if (!map)
		return (NULL);
	ft_bzero(map, sizeof(*map));
	map->player_coords.x = BAD_COORD;
	map->player_coords.y = BAD_COORD;
	map->last_collision.x = BAD_COORD;
	map->last_collision.y = BAD_COORD;
	return (map);
}

void	error_exit(t_game *game, int return_value, char *message)
{
	if (return_value)
	{
		ft_putendl_fd(message, 2);
	}
	if (game != NULL)
		mlx_do_key_autorepeaton(game->mlx.id);
	exit(return_value);
}

t_img	initialize_img(t_img *img, void *mlx_ptr, int width, int height)
{
	img->mlx_img = mlx_new_image(mlx_ptr, width, height);
	if (img->mlx_img == NULL)
		error_exit(NULL, 1, "Memory allocation error: t_img");
	img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_length, &img->endian);
	img->size = (t_vector){width, height};
	img->aspect = (float)img->size.x / (float)img->size.y;
	return (*img);
}

char	*get_full_texture_path(char *line, int flag)
{
	char	*new_line;

	new_line = line;
	if (flag)
	{
		new_line = ft_strcat_delim(ASSETS_PATH, '/', line);
		free(line);
	}
	return (new_line);
}
