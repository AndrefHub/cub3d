#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "stdio.h"

# define BAD_FILE -2
# define BAD_COLOUR (1 << 24)
# define BAD_COORD -1

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_map
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F;
	int		C;
	t_vector	player_coords;
	char	player_orient;
} t_map;

// typedef struct s_game
// {
// 	t_map		*map;
// } t_game;

int		check_longer_row_border(char *shorter, int sindex, int lindex, char direct);
int		check_longer_row_border_vert(t_list *map, int x, int sindex, int lindex, char direct);
int		get_non_space_index_left(char *line);
int		get_non_space_index_right(char *line);
int		get_non_space_index_top(t_list *map, int x);

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
int		find_player(t_map *map, char *line);
int		is_enclosed(t_map *args);

t_map	*create_empty_map(void);

int		ft_arraylen(void **arr);

#endif