/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:44 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:47:46 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

static int	filename_check(char *filename)
{
	if (ft_strlen(filename) < 5 || ft_strncmp(&filename
			[ft_strlen(filename) - 4], ".cub", 4) != 0)
		return (0);
	return (1);
}

static int	file_exists(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	return (fd);
}

int	check_file(int ac, char **av)
{
	int	fd;

	fd = -1;
	if (ac != 2)
		return (BAD_FILE);
	if (filename_check(av[1]) == 0)
		return (BAD_FILE);
	fd = file_exists(av[1]);
	if (fd == 0)
		return (BAD_FILE);
	return (fd);
}
