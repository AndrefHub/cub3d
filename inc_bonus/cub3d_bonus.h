#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdbool.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "stdio.h"
# include "constants_bonus.h"
# include "math.h"
# include "X11/X.h"
# include "X11/keysym.h"
//# include
# include <time.h>
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

typedef struct rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}	t_rgb;

// t_text: dummy structure created with sole purpose of
// putting 5 variables in function
typedef struct text
{
	char		*text;
	t_vector	pos;
	int			layout;
}	t_text;

typedef struct s_map
{
	int				bonus;
	int				path_prefix;
	char			**map;
	t_vector		map_size;
	t_texture		walls[MAX_WALL_CHARS];
	t_texture		enemy[MAX_ENEMIES];
	t_texture		font[MAX_FONT_CHARS];
	char			*sounds[MAX_SOUNDS];
	unsigned int	list_size;
	int				f;
	int				c;
	t_img			img;
	t_vector		player_coords;
	float			player_orient;
	int				map_tile_size;
	t_fvector		last_collision;
	t_list			*enemies;
	t_list			*objects;
}				t_map;

typedef struct ray
{
	t_fvector	unit;
	t_fvector	dir;
	t_vector	map_tile;
	t_fvector	length;
	t_vector	step;
}				t_ray;

typedef struct sound
{
	cs_loaded_sound_t	file;
	cs_play_sound_def_t	def;
	cs_playing_sound_t	*play;
}				t_sound;

typedef struct s_game_object
{
	t_fvector	pos;
	int			fade;
	t_vector	start;
	t_vector	end;
	t_vector	size;
	t_fvector	render_step;
	float		distance;
	t_img		*sprite;
	char		type;
}				t_object;

typedef struct s_enemy
{
	t_object	*object;
	t_fvector	delta;
	t_ull		last_attack_time;
	t_fvector	starting_pos;
}				t_enemy;

typedef struct s_hud_entry
{
	int		value;
	char	*title;
	short	title_size;
	short	value_size;
}				t_hud_entry;

typedef struct game
{
	t_map			*map;
	char			**grid;
	bool			show_map;
	t_img			img;
	t_img			hud_img;
	int				z_offset;
	float			fov;
	t_list			*objects;
	struct			s_mlx
	{
		void		*id;
		void		*window;
	}	mlx;
	struct			s_player
	{
		t_fvector	pos;
		t_fvector	delta;
		t_ull		last_attack_time;
		float		angle;
		t_fvector	vector;
		// short		lives;
		// short		health;
		t_fvector	starting_pos;
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
	struct			s_audio
	{
		cs_context_t	*ctx;
		t_sound			bonk;
		t_sound			song;
	}					audio;
	struct	s_time
	{
		t_ull		startup;
		int			frames_to_move;
		t_ull		last;
		t_ull		fps_time;
		int			fps;
		char		*fps_title;
	}				time;
	struct s_hud
	{
		t_hud_entry		fps;
		t_hud_entry		score;
		t_hud_entry		lives;
		t_hud_entry		health;
	}			hud;
	char			*macos_chars;
	char			*username;
	int				input_mode;
}	t_game;

// Font parsing: parsing_font.c //
void	parse_font(t_map *map, int fd, char **line);

// Map parsing: parsing.c //
int		get_string_index(char *str, char c);
char	**lst_to_array(t_list *tmp); // TODO: Move to another file
void	empty_func(void *ptr);
void	parse_map(t_map *map, int fd); //TODO: Rename
t_map	*parse_file(int ac, char **av);

// Parsing utils: parsing_utils.c //
t_map	*free_map(t_map *map);
int		ft_strrchr_int(const char *line, int chr);
int		ft_strrchr_int_arr(const char *line, char *chr);
void	map_to_rectangle(t_map *map); // TODO: Rename "set_map_to_rectangle"?
void	convert_spaces_to_zeros(t_map *map);

// Parsing textures path from map: parsing_textures.c //
void	parse_config(t_map *map, int fd, char **line);
void	parse_walls(t_map *map, int fd, char **line);
void	parse_enemies(t_map *map, int fd, char **line);
void	parse_sounds(t_map *map, int fd, char **line);
void	parse_assets(t_map *map, int fd);

// Check filename and : check_file.c //
int		check_file(int ac, char **av);

// Cub3d utils : ft_utils.c //
t_map	*create_empty_map(void);
int		ft_arraylen(void **arr);
int		is_space(char c);
int		is_line_empty(char *line);
void	error_exit(t_game *game, int return_value, char *message);
t_img	initialize_img(t_img *img, void *mlx_ptr, int width, int height);
void	print_map_debug(t_map *map);
char	*get_full_texture_path(char *line, int flag);
float	distancef(t_fvector *vector1, t_fvector *vector2);

// Some utils for parsing and working with files: input_manip.c //
char	*crop_prefix(char *line, char *prefix);
char	*skip_empty_lines(int fd);
int		convert_to_rgb(char *line);
char	*ft_strcat_delim(char *first, char delim, char *second);

// Border checking and utils for it: border_checking.c //
int		get_map_width(const char **map); //TODO: Move to another file
int		is_wall(char c);
int		is_enemy(char c);
int		check_enclosure(t_map *map, t_vector vec);
int		is_map_enclosed(t_map *args);

// Find objects (player, enemies, coins): find_objects.c //
int		set_player(t_map *map, t_list *lst, char *line, char *orient);
void	find_enemy(t_list **lst, t_object *object);
void	find_objects(t_map *map);
int		find_player(t_map *map, char *line, t_list *lst);

// Game initialization: start_game.c //
void	initialize_mlx_parameters(t_game *game);
void	initialize_player(t_game *game);
void	initialize_game_parameters(t_game *game);
void	start_game(t_game *game);
int		game(t_map *map);

// Work with sound: game_sound.c //
void	init_main_game_sound_theme(t_game *game,
			char *main_music_theme_filename);
void	set_game_events_sounds(struct s_audio *audio, char *filename);
void	set_sound(t_sound *sound, char *filename);

// Work with sprites: game_textures.c //
void	draw_texture_set(t_game *game, struct s_column *column);
void	import_texture_to_img(t_game *game, t_img *img, char *filename,
			int img_size);
void	initialize_sprites(t_game *game, int size, t_texture *sprites_list,
			int t_size);
void	initialize_wall_textures(t_game *game);

// Adapters for MLX for macOS and Linux: mlx_adapter.c //
void	mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);
void	mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
void	mouse_show(void *mlx_ptr, void *win_ptr);
void	mouse_hide(void *mlx_ptr, void *win_ptr);

// Everything about drawing: drawing.c //
void	put_pixel(t_img *img, t_vector point, int color);
void	draw_line(t_img *img, t_vector p1, t_vector p2, int color);
void	draw_square_fill(t_img *img, t_vector top_left, int size, int color);
void	fill_img_color(t_img *img, int color);
void	fill_floor_color(t_img *img, int color, int horizon);
void	fill_ceiling_color(t_img *img, int color, int horizon);
void	draw_aim(t_game *game); //TODO: ??

// Main game loop: game_loop.c //
int		game_loop(t_game *game);

// : controller.c //
int		float_sign(float f);
void	open_door(t_game *game);
void	change_textures(t_game *game);
float	fvector_distance(t_fvector lhs, t_fvector rhs);
void	enemy_attack(t_game *game, t_enemy *enemy);
void	enemy_move(t_game *game);

// Player input control: player_controller.c //
void	player_delta_calculation(struct s_player *player);
void	mouse_controller(t_game *game);
void	movement_controller(t_game *game, int *collision);
void	rotation_by_key_controller(t_game *game);
void	player_controll(t_game *game);

// Player moving control: player_movement.c //
void	update_last_collision(t_game *game);
void	move_radius_check(t_game *game, float x_delta, float y_delta,
			int *collision);
void	check_restrictions(t_game *game);
void	check_borders(t_game *game, t_object *player);

// Drawing ceil and floor textured: draw_ceil_floor.c //
void	draw_ceil_textured(t_game *game);

// Ray_casting algorithm: ray_casting.c //
t_ray	ray_initialize(t_game *game, float ray_angle);
float	interception_distance(t_game *game, t_ray *ray);
void	initialize_columns(t_game *game, t_ray *ray, float distance, int i,
			float ray_angle);
void	get_interception(t_game *game, float ray_angle, int i); //DDA algorithm
void	cast_rays(t_game *game);

// Wall drawing: draw_walls.c //
void	draw_wall_scaled(t_img *img, const t_img *texture,
			const struct s_column *column, int x, t_game *game);
void	draw_walls(t_game *game);

// Map drawing: draw_map.c //
void	draw_fps(t_game *game);
void	draw_enemies_on_map(t_game *game);
void	draw_player_on_map(t_game *game);
void	draw_hud(t_game *game);
void	draw_map(t_game *game);

// Text writing: put_text.c //
int		put_char_to_screen(t_game *game, char c, t_vector pos, int divisor);
void	put_text_to_screen(t_game *game, char *text, t_vector pos, int divisor);
void	put_text_to_screen_layout(t_game *game, t_text *text, int divisor);
void	put_image_to_image(t_img *dst, t_vector pos, t_img *src);

void	input_mode(int key, t_game *game);

// Death events: death_events.c //
void	death_message(t_game *game);
void	player_death(t_game *game);
int		check_aliveness(t_game *game);
void	dim_image(t_img *img, int img_size, t_rgb *color);
void	dim_screen(t_game *game, int i);

// Drawing enemies: draw_enemies.c //
int		object_comparator(t_object *obj1, t_object *obj2);
void	draw_game_objects(t_game *game);

// void	initialize_font(t_map *map);

//controller.c
int		close_hook(t_game *game);
int		key_hook_press(int key, t_game *game);
int		key_hook_release(int key, t_game *game);
int		mouse_hook_press(int button, int x, int y, t_game *game);
int		mouse_hook_release(int button, int x, int y, t_game *game);

bool	key_pressed(t_game *game, int key);

//demo
void	error_exit(t_game *game, int return_value, char *message);

// time
t_ull	get_time(void);
t_ull	get_time_hp(void);
void	init_time(t_game *game);
void	wait_milliseconds(int milliseconds);

void	ft_lstsort(t_list **lst, int (*cmp)());
void	update_time(t_game *game);

// downscale_image.c //
void	put_downscaled_image(t_img *dst, t_vector pos, t_img *src, int divisor);

void	put_frame(t_game *game);

void	init_hud(struct s_hud *hud);

// what happens to player after death: // 
int	player_respawn(t_game *game);

// is_checks.c //
int		is_wall(char c);
int		is_enemy(char c);
int		is_edible(char c);
int		is_object(char c);

// player_eating.c //
void	ft_lstdelbyaddr(t_list **lst, t_list *to_del, void (*del)(void *));
void	eat_by_coords(t_game *game, t_vector pos);
void	player_eat(t_game *game);

#endif
