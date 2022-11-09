/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:46:47 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:46:48 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_map	*create_empty_map(void)
{
	t_map	*map;

	map = malloc(sizeof(*map));
	if (!map)
		return (NULL);
	ft_bzero(map, sizeof(*map));
	map->player_coords.x = BAD_COORD;
	map->player_coords.y = BAD_COORD;
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
