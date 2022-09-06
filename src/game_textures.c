#include "../inc/cub3d.h"

void	draw_texture_set(t_game *game, struct s_column *column)
{
	const char chr = game->grid[column->cell.y][column->cell.x];

	column->texture_id = ft_strchr(WALL_CHARS, chr) - WALL_CHARS;
	//		texture_id = ft_strchr(CARDINAL_POINTS, game->column[x].dir) - CARDINAL_POINTS;
}

void	import_texture_to_img(t_game *game, t_img *img, char *filename)
{
	int	size;

	size = TEXTURE_SIZE;
	if (ft_strlen(filename) < 5)
		error_exit(game, 1, "Initialization fail: Invalid texture filename");
	if (ft_strncmp(".xpm", &filename[ft_strlen(filename) - 4], 4) == 0)
		img->mlx_img = mlx_xpm_file_to_image(game->mlx.id, filename, &size, &size);
	else
		error_exit(game, 1, "Initialization fail: Invalid texture format");
	if (img->mlx_img == NULL)
		error_exit(game, 1, "Initialization fail: Textures loading");
	img->addr = (int *) mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_length, &img->endian);
	img->size.x = TEXTURE_SIZE;
	img->size.y = TEXTURE_SIZE;
}

void	initialize_sprites(t_game *game)
{
	t_list	*img_list;
	t_list	*texture_list;
	t_img	*img;
	int		counter;

	counter = -1;
	while (++counter < MAX_WALL_CHARS)
	{
		texture_list = game->map->texture_list[counter];
		img_list = NULL;
		while (texture_list)
		{
			img = malloc(sizeof(*img));
			if (img == NULL)
				error_exit(game, 1, "Memory allocation error: Sprites initializing");
			import_texture_to_img(game, img, texture_list->content);
			ft_lstadd_back(&img_list, ft_lstnew(img));
			texture_list = texture_list->next;
		}
		game->map->img_list[counter] = img_list;
		if (img_list)
		{
			ft_lstlast(img_list)->next = img_list;
			game->textures[counter] = *(t_img *) game->map->img_list[counter]->content;
		}
	}
}