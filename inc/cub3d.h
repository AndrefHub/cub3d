#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "stdio.h"
# include "constants.h"
# include "math.h"
# include "/opt/X11/include/X11/X.h"
# include "/opt/X11/include/X11/keysym.h"

# define BAD_FILE -2
# define BAD_COLOUR (1 << 24)
# define BAD_COORD -1

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_fvector
{
	float	x;
	float	y;
}	t_fvector;

typedef struct s_map
{
	t_list	*map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F;
	int		C;
	t_vector	player_coords;
	char	player_orient;
} t_map;

typedef struct s_img
{
	void		*mlx_img;
	int			*addr;
	int			bpp;
	int			line_length;
	int			endian;
	t_vector	size;
}	t_img;

typedef struct game
{
	struct s_mlx
	{
		void	*id;
		void	*window;
	}	mlx;
	t_map			*map;
	char			**grid;
	t_img			img;
	int				size;
	int				frames;
	int				init_render;
	struct			s_player
	{
		t_fvector	pos;
		float	angle;
		t_fvector	vector;
		t_fvector	delta;
		t_fvector	plane;
	}	player;
}	t_game;

// typedef struct s_game
// {
// 	t_map		*map;
// } t_game;

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

//controller.c
int	close_hook(t_game *game);
int	key_hook_press(int key, t_game *game);
int	game_loop(t_game *game);

//drawing.c
void	draw_map(t_game *game);
void	draw_line(t_img *img, t_vector p1, t_vector p2, int color);
void	put_pixel(t_img *img, t_vector point, int color);
void	draw_square_fill(t_img *img, t_vector top_left, int size, int color);
void	draw_player(t_game *game);
void	img_clear_rgb(t_img *img, int color);

//demo
char	**charlist_to_matrix(t_list *list);
#endif