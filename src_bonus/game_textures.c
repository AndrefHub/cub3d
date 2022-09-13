#include "../inc_bonus/cub3d_bonus.h"

void	draw_texture_set(t_game *game, struct s_column *column)
{
	const char chr = game->grid[column->cell.y][column->cell.x];

	column->texture_id = ft_strchr(WALL_CHARS, chr) - WALL_CHARS;
	//		texture_id = ft_strchr(CARDINAL_POINTS, game->column[x].dir) - CARDINAL_POINTS;
}

void	import_texture_to_img(t_game *game, t_img *img, char *filename, int img_size)
{
	int	size;

	size = TEXTURE_SIZE;
	if (ft_strlen(filename) < 5)
		error_exit(game, 1, "Initialization fail: Invalid texture filename");
	if (ft_strncmp(".xpm", &filename[ft_strlen(filename) - 4], 4) == 0)
	{
		img->mlx_img = mlx_xpm_file_to_image(game->mlx.id, filename, &size,
											 &size);
	}
	else
		error_exit(game, 1, "Initialization fail: Invalid texture format");
	if (img->mlx_img == NULL) {
		ft_putendl_fd(filename, 2);
		error_exit(game, 1, "Initialization fail: Textures loading");
	}
	img->addr = (int *) mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_length, &img->endian);
	img->size.x = img_size;
	img->size.y = img_size;
}

void	initialize_sprites(t_game *game, int size, t_texture *sprites_list, int t_size)
{
	t_list	*texture_list;
	t_img	*img;
	int		c;

	c = -1;
	while (++c < size)
	{
		texture_list = sprites_list[c].texture;
		sprites_list[c].img = NULL;
		while (texture_list)
		{
			img = malloc(sizeof(*img));
			if (img == NULL)
				error_exit(game, 1, "Memory allocation error: Sprites \
					initializing");
			import_texture_to_img(game, img, texture_list->content, t_size);
			ft_lstadd_back(&sprites_list[c].img, ft_lstnew(img));
			texture_list = texture_list->next;
		}
		if (sprites_list[c].img)
		{
			ft_lstlast(sprites_list[c].img)->next = sprites_list[c].img;
			game->textures[c] = *(t_img *) sprites_list[c].img->content;
		}
	}
}