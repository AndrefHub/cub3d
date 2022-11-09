/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:14 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 19:08:35 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	free_texture_lists(t_game *game)
{
	int	i;

	i = -1;
	while (++i < MAX_WALL_CHARS)
		ft_lstclear(&game->map->walls[i].texture, free);
}
