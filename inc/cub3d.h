#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "stdio.h"
# include "constants.h"
# include "math.h"
# include "X11/X.h"
# include "X11/keysym.h"
//# include
# include "time.h"
# include <sys/time.h>
# include "../cute_sound/cute_sound.h"
# ifdef __APPLE__
#  include "../mlx/mlx.h"
# else
#  include "../mlx_linux/mlx.h"
# endif

typedef unsigned long long	t_ull;

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

typedef struct s_texture
{
	t_list	*texture;
	t_list	*img;
}	t_texture;

typedef struct s_map
{
	int			bonus;
	int			path_prefix;
	char		**map;
	t_vector	map_size;
	t_texture	walls[MAX_WALL_CHARS];
	t_texture	entity[MAX_ENTITIES];
	unsigned	list_size;
	int			F;
	int			C;
	t_img		img;
	t_vector	player_coords;
	float		player_orient;
	int			map_tile_size;
	t_fvector	last_collision;
	t_list		*enemies;	
} t_map;

typedef struct ray
{
	t_fvector	unit;
	t_fvector	dir;
	t_vector	map_tile;
	t_fvector	length;
	t_vector	step;
}				t_ray;

typedef struct	sound
{
	cs_loaded_sound_t	file;
	cs_play_sound_def_t	def;
}				t_sound;

typedef struct	s_enemy
{
	t_img		sprite;
	t_fvector	pos;
}				t_enemy;

typedef struct game
{
	t_map			*map;
	char			**grid;
	bool			show_map;
	t_img			img;

	struct s_mlx
	{
		void	*id;
		void	*window;
	}	mlx;

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
		float		perp_dist;
		t_fvector	pos;
		int			side;
		t_fvector	ray_dir;
		t_vector	cell;
		char		dir;
		int			height;
		uint32_t	texture_id;
		float		texture_pos;
		float		fade;
		int			color;
	}				*column;
	t_img			textures[MAX_WALL_CHARS];

	struct				s_audio
	{
		cs_context_t	*ctx;

		t_sound			bonk;
		t_sound			song;
	}					audio;
	struct 	s_time
	{
		t_ull	startup;
		int		frames_to_move;
		t_ull	last;
	}		time;
	
}	t_game;


// Map parsing: parsing.c //
t_map	*parse_file(int ac, char **av);
void	get_textures(t_map *map, int fd); //TODO: Rename "get_textures_from_file"
void	get_map(t_map *map, int fd); //TODO: Rename
char	**lst_to_char_ptr(t_list *tmp); // TODO: Move to another file
void	map_to_rectangle(t_map *map); // TODO: Rename "set_map_to_rectangle"?
void	convert_spaces_to_zeros(t_map *map);
int		ft_strrchr_int(const char *line, int chr);
t_map	*free_map(t_map *map);
char	**lst_to_char_ptr(t_list *tmp); //TODO: Rename "lst_to_char_matrix"


// Check filename and : check_file.c //
int		check_file(int ac, char **av);


// Cub3d utils : ft_utils.c //
t_map	*create_empty_map();
int		ft_arraylen(void **arr);
int		ft_is_empty(char *line); //TODO: Rename "is_line_empty"
t_img	initialize_img(t_img *img, void *mlx_ptr, int width, int height);


// Some utils for parsing and working with files: input_manip.c //
int		convert_rgb(char *line); //TODO: Rename
char	*skip_empty_lines(int fd);



// Border checking and utils for it: border_checking.c //
int		find_player(t_map *map, char *line, t_list *lst); //TODO: Rename "find_player_on_map"
void	find_enemy(t_map *map);
int		get_map_width(const char **map); //TODO: Move to another file
int		is_enclosed(t_map *args); //TODO: Rename "is_map_enclosed"
int		check_enclosure(t_map *map, t_vector vec);


// Game initialization: start_game.c //
int		game(t_map *map);

// Work with sound: game_sound.c //
void	init_main_game_sound_theme(t_game *game, char *main_music_theme_filename);
void	set_game_events_sounds(struct s_audio *audio);
void	set_sound(t_sound *sound, char *filename);


// Work with sprites: game_sprites.c //
void	initialize_sprites(t_game *game, int size, t_texture *sprites_list);
void	import_texture_to_img(t_game *game, t_img *img, char *filename);
void	draw_texture_set(t_game *game, struct s_column *column);

// Adapters for MLX for macOS and Linux: mlx_adapters.c //
void	mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);
void	mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
void	mouse_show(void *mlx_ptr, void *win_ptr);
void	mouse_hide(void *mlx_ptr, void *win_ptr);

// Everything about drawing: drawing.c //
void	put_pixel(t_img *img, t_vector point, int color);
void	draw_line(t_img *img, t_vector p1, t_vector p2, int color);
void	draw_square_fill(t_img *img, t_vector top_left, int size, int color);
void	fill_img_color(t_img *img, int color);
void	fill_floor_color(t_img *img, int color);
void	fill_ceiling_color(t_img *img, int color);
void	draw_aim(t_game *game); //TODO: ??



int		check_file(int ac, char **av);
char	*crop_prefix(char* line, char *prefix);
int		is_space(char c);
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
char	*ft_strcat_delim(char *first, char delim, char *second);
t_map	*create_empty_map(void);
int		is_wall(char c);
int		ft_arraylen(void **arr);
int		get_string_index(char *str, char c);
void	get_textures_list(t_map* map, int fd, char **line);
void	get_entity(t_map* map, int fd, char **line);
char	*get_full_texture_path(char *line, int flag);

// char	*get_textures_list(int fd, char *prefix, t_list **lst);
//controller.c
int		close_hook(t_game *game);
int		key_hook_press(int key, t_game *game);
int		key_hook_release(int key, t_game *game);
int		mouse_hook_press(int button, int x, int y, t_game *game);
int		mouse_hook_release(int button, int x, int y, t_game *game);
int		game_loop(t_game *game);

//drawing.c
void	draw_map(t_game *game);
void	draw_line(t_img *img, t_vector p1, t_vector p2, int color);
void	put_pixel(t_img *img, t_vector point, int color);
void	draw_square_fill(t_img *img, t_vector top_left, int size, int color);
void	draw_player(t_game *game);
void	draw_aim(t_game *game);
void	fill_img_color(t_img *img, int color);
void	cast_rays(t_game *game);
void	get_interception(t_game *game, float ray_angle, int i); //DDA algorithm
bool	key_pressed(t_game *game, int key);
void	draw_walls(t_game *game);
void	draw_fps(t_game *game);

//demo
char	**charlist_to_matrix(t_list *list);

void	error_exit(t_game *game, int return_value, char *message);

void	open_door(t_game *game);
// time
t_ull	get_time(void);
void	init_time(t_game *game);
void	wait_milliseconds(int milliseconds);

void	draw_texture_set(t_game *game, struct s_column *column);
#endif
