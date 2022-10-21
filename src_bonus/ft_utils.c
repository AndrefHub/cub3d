#include "../inc_bonus/cub3d_bonus.h"

t_map	*create_empty_map(void)
{
	t_map	*map;
	// int		counter;

	// counter = -1;
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

int	ft_arraylen(void **arr)
{
	int	counter;

	counter = 0;
	while (arr && arr[counter])
		++counter;
	return (counter);
}

int	is_space(char c)
{
	return (c != ' ' && c != '\t' && c != '\n');
}

int		is_line_empty(char *line)
{
	while (line && *line)
	{
		if (is_space(*line))
			return (0);
		++line;
	}
	return (1);
}

void	error_exit(t_game *game, int return_value, char *message)
{
	if (return_value)
	{
		ft_putendl_fd(message, 2);
	}
	//free(all)
	// (void ) game;
	if (game != NULL)
		mlx_do_key_autorepeaton(game->mlx.id);
	exit(return_value);
}

t_img	initialize_img(t_img *img, void *mlx_ptr, int width, int height)
{
	img->mlx_img = mlx_new_image(mlx_ptr, width, height);
	if (img->mlx_img == NULL)
		error_exit(NULL, 1, "Memory allocation error: t_img");
	img->addr = (int *) mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_length, &img->endian);
	img->size = (t_vector) {width, height};
	img->aspect = (float) img->size.x / (float) img->size.y;
	return (*img);
}

void	print_map_debug(t_map *map)
{
	char	**ptr;

	printf("NO %s\nSO %s\nWE %s\nEA %s\nF %d,%d,%d\nC %d,%d,%d\n\n",
		(char *)map->walls[0].texture->content, (char *)map->walls[1].texture->content,
		(char *)map->walls[2].texture->content, (char *)map->walls[3].texture->content,
		map->f >> 16, (map->f >> 8) % (1 << 8), map->f % (1 << 8),
		map->c >> 16, (map->c >> 8) % (1 << 8), map->c % (1 << 8));
	printf("Player X: %d\nPlayer Y: %d\nPlayer orientation: %f\n",
		map->player_coords.x, map->player_coords.y, map->player_orient);
	ptr = map->map;
	while (*ptr)
	{
		printf("%s\n", *ptr);
		++ptr;
	}
	 printf("\nIs enclosed? %d\n", is_map_enclosed(map));
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

float	distancef(t_fvector *vector1, t_fvector *vector2)
{
	return (sqrtf(powf(vector2->x - vector1->x, 2)
				  + powf(vector2->y - vector1->y, 2)));
}

/*
void	foo()
{
	//FLOOR CASTING
	for(int y = 0; y < h; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = dirX - planeX;
		float rayDirY0 = dirY - planeY;
		float rayDirX1 = dirX + planeX;
		float rayDirY1 = dirY + planeY;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - screenHeight / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * screenHeight;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = posX + rowDistance * rayDirX0;
		float floorY = posY + rowDistance * rayDirY0;

		for(int x = 0; x < screenWidth; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;
			Uint32 color;

			// floor
			color = texture[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			buffer[y][x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = texture[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			buffer[screenHeight - y - 1][x] = color;
		}
	}
}*/
