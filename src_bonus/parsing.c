/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:10 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:50:12 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

// int	is_prefix_number(char *line, char *prefix, int counter)
// {
// 	return (line && !ft_strncmp(line, prefix, ft_strlen(prefix))
// 		&& (ft_atoi(line + ft_strlen(prefix)) == counter + 1
// 			|| (counter == 0 && line[ft_strlen(prefix) + 1] == ' ')));
// }

int	get_string_index(char *str, char c)
{
	int	index;

	index = -1;
	while (str[++index])
		if (str[index] == c)
			return (index);
	return (-1);
}

char	**lst_to_array(t_list *tmp)
{
	char	**map;
	int		counter;
	int		size;

	size = ft_lstsize(tmp);
	map = malloc(sizeof(*map) * (size + 1));
	if (map)
	{
		counter = -1;
		while (++counter < size)
		{
			map[counter] = tmp->content;
			tmp = tmp->next;
		}
		map[size] = NULL;
	}
	return (map);
}

void	empty_func(void *ptr)
{
	(void) ptr;
}

void	parse_map(t_map *map, int fd)
{
	char	*line;
	t_list	*tmp;

	tmp = NULL;
	line = skip_empty_lines(fd);
	while (line && !is_line_empty(line))
	{
		ft_lstadd_back(&tmp, ft_lstnew(line));
		find_player(map, line, tmp);
		line = skip_empty_lines(fd);
	}
	free(line);
	if (map->player_coords.x == BAD_COORD)
		error_exit(NULL, 1, "Reading error: Player not found");
	map->map = lst_to_array(tmp);
	find_objects(map);
	ft_lstclear(&tmp, empty_func);
	map->map_size.x = get_map_width((const char **)map->map);
	map->map_size.y = ft_arraylen((void **) map->map);
	map_to_rectangle(map);
}

t_map	*parse_file(int ac, char **av)
{
	t_map	*map;
	int		fd;

	fd = check_file(ac, av);
	if (fd != BAD_FILE)
	{
		map = create_empty_map();
		map->map_file = av[1];
		if (map == NULL)
			error_exit(NULL, 1, "Allocation error: Map");
		parse_assets(map, fd);
		parse_map(map, fd);
		if (map->map_size.x == 0 || map->map_size.y == 0)
			error_exit(NULL, 1, "Reading error: Map");
		if (is_map_enclosed(map))
		{
			convert_spaces_to_zeros(map);
			return (map);
		}
		else
			error_exit(NULL, 1, "Reading error: Map not enclosed");
	}
	else
		error_exit(NULL, 1, "Invalid input file: Map");
	return (NULL);
}
