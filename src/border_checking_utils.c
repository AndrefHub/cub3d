#include "../inc/cub3d.h"

int	check_longer_row_border(char *shorter, int sindex, int lindex, char direct)
{
	if (direct == 'l')
	{	
		while (shorter[sindex] == '1' && sindex <= lindex)
			++sindex;
		printf("sindex = %d, lindex = %d\n", sindex, lindex);
		return (sindex <= lindex);
	}
	while (shorter[sindex] == '1' && sindex >= lindex)
		--sindex;
	printf("sindex = %d, lindex = %d\n", sindex, lindex);
	return (sindex >= lindex);
}

int	check_longer_row_border_vert(char **map, int x, int sindex, int lindex, char direct)
{
	if (direct == 't')
	{	
		while ((map[sindex][x] == '1' || map[sindex][x] == ' ') && sindex <= lindex)
			++sindex;
		printf("sindex = %d, lindex = %d\n", sindex, lindex);
		return (sindex <= lindex);
	}
	while (map[sindex][x] == '1' && sindex >= lindex)
		--sindex;
	printf("sindex = %d, lindex = %d\n", sindex, lindex);
	return (sindex >= lindex);
}

int	get_non_space_index_left(char *line)
{
	int	index;

	if (!ft_strchr(line, '1'))
		return (0);
	index = 0;
	while (line[index] == ' ')
		++index;
	return (index);
}

int	get_non_space_index_right(char *line)
{
	int	index;

	if (!ft_strchr(line, '1'))
		return (0);
	index = ft_strlen(line) - 1;
	while (line[index] == ' ')
		--index;
	return (index);
}

int	get_non_space_index_top(char **map, int x)
{
	int	index;

	index = 0;
	while (map[index] && (x > (int)ft_strlen(map[index])
		|| (map[index][x] == ' ')))
		++index;
	if (!map[index])
		return (0);
	return (index);
}
