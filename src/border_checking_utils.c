#include "../cub3d.h"

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

int	check_longer_row_border_vert(t_list *map, int x, int sindex, int lindex, char direct)
{
	if (direct == 't')
	{	
		while ((((char *)ft_lstat(map, sindex)->content)[x] == '1' || ((char *)ft_lstat(map, sindex)->content)[x] == ' ') && sindex <= lindex)
			++sindex;
		printf("sindex = %d, lindex = %d\n", sindex, lindex);
		return (sindex <= lindex);
	}
	while (((char *)ft_lstat(map, sindex)->content)[x] == '1' && sindex >= lindex)
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

int	get_non_space_index_top(t_list *map, int x)
{
	int	index;

	index = 0;
	while (ft_lstat(map, index) && (x > (int)ft_strlen(ft_lstat(map, index)->content)
		|| (((char *)ft_lstat(map, index)->content)[x] == ' ')))
		++index;
	if (!ft_lstat(map, index))
		return (0);
	return (index);
}