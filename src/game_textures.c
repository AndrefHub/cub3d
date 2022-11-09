#include "../inc/cub3d.h"

void	draw_texture_set(t_game *game, struct s_column *column)
{
	column->texture_id = ft_strchr(WALL_CHARS, game->grid
		[column->cell.y][column->cell.x]) - WALL_CHARS;
}

void	skip_transparent_background(t_img *img)
{
	int		x;
	int		y;
	short	opaque_pix_y;

	x = 0;
	while (x < img->size.x)
	{
		y = 0;
		opaque_pix_y = INT16_MAX;
		img->alpha_start_x[x] = INT16_MAX;
		while (y < img->size.y)
		{
			if (img->addr[y * img->size.x + x] >> 24 == 0x00)
			{
				if (opaque_pix_y == INT16_MAX)
					img->alpha_start_x[x] = y;
				opaque_pix_y = (short) y;
			}
			y++;
		}
		img->alpha_end_x[x] = opaque_pix_y;
		x++;
	}
}

void	import_texture_to_img(t_game *game, t_img *img, char *filename, t_vector size)
{
	int	tex_size;

	tex_size = TEXTURE_SIZE;
	if (!filename)
		error_exit(game, 1, "Initialization fail: \
Missing texture filename or invalid entries order.");
	if (ft_strlen(filename) < 5)
		error_exit(game, 1, "Initialization fail: Invalid texture filename");
	if (ft_strncmp(".xpm", &filename[ft_strlen(filename) - 4], 4) == 0)
		img->mlx_img = mlx_xpm_file_to_image
			(game->mlx.id, filename, &tex_size, &tex_size);
	else
		error_exit(game, 1, "Initialization fail: Invalid texture format");
	if (img->mlx_img == NULL)
	{
		ft_putendl_fd(filename, 2);
		error_exit(game, 1, "Initialization fail: Textures loading");
	}
	img->addr = (int *) mlx_get_data_addr
		(img->mlx_img, &img->bpp, &img->line_length, &img->endian);
	img->size.x = size.x;
	img->size.y = size.y;
}

void	initialize_sprites(t_game *game, int size, t_texture *sprites_list, int t_size)
{
	char	*texture;
	t_img	*img;
	int		c;

	c = -1;
	while (++c < size)
	{
		texture = sprites_list[c].texture;
		sprites_list[c].img = NULL;
		img = malloc(sizeof(*img));
		if (img == NULL)
			error_exit(game, 1, "Memory allocation error: Sprites \
				initializing");
		import_texture_to_img(game, img, texture,
			(t_vector){t_size, t_size});
		sprites_list[c].img = img;
	}
}

void	initialize_wall_textures(t_game *game)
{
	int	counter;

	counter = -1;
	while (++counter < MAX_WALL_CHARS)
		game->textures[counter] = *game->map->walls[counter].img;
}
