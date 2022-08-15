#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "stdio.h"
# include "constants.h"
# include "math.h"
# include "/usr/local/include/X11/X.h"
# include "/usr/local/include/X11/keysym.h"
# include "time.h"

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

typedef struct s_img
{
	void		*mlx_img;
	int			*addr;
	int			bpp;
	int			line_length;
	int			endian;
	t_vector	size;
}	t_img;

typedef struct s_map
{
	char		**map;
	t_vector	map_size;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	int			F;
	int			C;
	t_img		img;
	t_vector	player_coords;
	int			player_orient;
} t_map;

typedef struct game
{
	struct s_mlx
	{
		void	*id;
		void	*window;
	}	mlx;
	t_map			*map;
	char			**grid;
	bool			show_map;
	t_img			img;
	int				fps;
	struct			s_player
	{
		t_fvector	pos;
		float		angle;
		t_fvector	vector;
		t_fvector	delta;
	}				player;
	struct			s_key
	{
		bool		k[512];
		bool		m[8];
		t_vector	mpos;
		t_vector	mdir;
		bool		mouse;
	}				key;
	struct			s_column
	{
		float		distance;
		t_fvector	pos;
		t_vector	cell;
		char		dir;
		int			height;
		//texture
		int			color;
	}				*column;

}	t_game;

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
int		find_player(t_map *map, char *line, t_list *lst);
int		is_enclosed(t_map *args);
int		get_map_width(char **map);

t_map	*create_empty_map(void);

int		ft_arraylen(void **arr);

//controller.c
int		close_hook(t_game *game);
int		key_hook_press(int key, t_game *game);
int		key_hook_release(int key, t_game *game);
int		game_loop(t_game *game);

//drawing.c
void	draw_map(t_game *game);
void	draw_line(t_img *img, t_vector p1, t_vector p2, int color);
void	put_pixel(t_img *img, t_vector point, int color);
void	draw_square_fill(t_img *img, t_vector top_left, int size, int color);
void	draw_player(t_game *game);
void	img_clear_rgb(t_img *img, int color);
void	draw_rays(t_game *game);
float	get_interception(t_game *game, float ray_angle, int i); //DDA algorithm
void	draw_3D(t_game *game);

//demo
char	**charlist_to_matrix(t_list *list);

int	get_non_space_index_left(char *line);
int	get_non_space_index_right(char *line);
int	get_non_space_index_top(char **map, int x);
int	check_longer_row_border(char *shorter, int sindex, int lindex, char direct);
int	check_longer_row_border_vert(char **map, int x, int sindex, int lindex, char direct);
#endif