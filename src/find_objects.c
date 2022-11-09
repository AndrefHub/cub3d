/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:46:45 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:46:47 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	set_player(t_map *map, t_list *lst, char *line, char *orient)
{
	int	x;

	x = ft_find_substr(line, orient);
	if (x != -1)
	{
		if (map->player_coords.x == BAD_COORD)
		{
			map->player_coords.x = x;
			map->player_coords.y = ft_lstsize(lst);
			if (*orient == 'E')
				map->player_orient = 0;
			if (*orient == 'N')
				map->player_orient = PI / 2;
			if (*orient == 'W')
				map->player_orient = PI;
			if (*orient == 'S')
				map->player_orient = 3 * PI / 2;
		}
		else
			return (BAD_COORD);
	}
	return (0);
}

int	find_player(t_map *map, char *line, t_list *lst)
{
	int	return_code;

	return_code = set_player(map, lst, line, "N");
	return_code += set_player(map, lst, line, "S");
	return_code += set_player(map, lst, line, "W");
	return_code += set_player(map, lst, line, "E");
	return (return_code);
}
