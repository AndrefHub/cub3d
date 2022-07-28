#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "stdio.h"

# define BAD_FILE -2
# define BAD_COLOUR (1 << 24)

typedef struct s_map
{
	t_list	*map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F;
	int		C;
} t_map;

int		check_file(int ac, char **av);
char	*crop_prefix(char* line, char *prefix);
int		ft_is_empty(char *line);
char	*skip_empty_lines(int fd);
char	*get_texture(int fd);
int		convert_rgb(char *line);
void	get_textures(t_map *map, int fd);
void	get_map(t_map *map, int fd);
t_map	*parse_file(int ac, char **av);
void	print_map_debug(t_map *map);
int		is_enclosed(t_map *args);

t_map	*create_empty_map(void);

int		ft_arraylen(void **arr);

#endif