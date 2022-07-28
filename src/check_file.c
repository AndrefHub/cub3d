#include "../cub3d.h"

int	check_file(int ac, char **av)
{
	int fd;

	if (ac != 2)
		return (BAD_FILE);
	if (ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".cub", 4) != 0)
		return (BAD_FILE);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (BAD_FILE);
	return (fd);
}