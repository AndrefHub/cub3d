#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "constants.h"

# include <stdbool.h>
# include <stdlib.h>
# include "stdio.h"
# include "math.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include <time.h>
# include <signal.h>
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
	float		aspect;
	short		*alpha_start_x;
	short		*alpha_end_x;
	t_vector	size;
}	t_img;

typedef struct s_texture
{
	char	*texture;
	t_img	*img;
}	t_texture;

typedef struct rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}	t_rgb;

typedef struct node
{
	t_vector	pos;	
	short		g;
	short		h;
	struct node	*parent;
} t_astar_node;

typedef t_astar_node t_node;

typedef struct s_astar
{
	t_list	*open;
	t_list	*closed;
}	t_astar_utils;

typedef struct s_scene
{
	void	(*scene_func)(void*);
	void	*parameter;
}	t_scene;

typedef struct text
{
	char		*text;
	t_vector	pos;
	int			layout;
	int			color;
}	t_text;

typedef struct s_map
{
	int				bonus;
	int				path_prefix;
	char			**map;
	t_vector		map_size;
	t_texture		walls[MAX_WALL_CHARS];
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
	char			*map_file;
}				t_map;

typedef struct ray
{
	t_fvector	unit;
	t_fvector	dir;
	t_vector	map_tile;
	t_fvector	length;
	t_vector	step;
}				t_ray;

typedef struct s_parse_info
{
	char		*chars;
	char		*prefix;
	t_texture	*arr;
	int			size;
} t_parse_info;

typedef struct game
{
	t_scene			scene;
	t_map			*map;
	char			**grid;
	bool			show_map;
	t_img			img;
	t_img			hud_img;
	t_img			hud_texture;
	int				z_offset;
	float			fov;
	float			col_step;
	float			col_scale;
	t_list			*objects;
	struct			s_mlx
	{
		void		*id;
		void		*window;
		t_vector	win_size;
		t_vector	game_size;
	}	mlx;
	struct			s_player
	{
		t_fvector	pos;
		t_fvector	delta;
		t_ull		last_attack_time;
		float		angle;
		t_fvector	plane;
		int			health;
		t_fvector	vector;
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
	t_list			*leaderboard;
	char			*macos_chars;
	int				panic_mode;
	int				input_mode;
	char			*death_message;
	char			*place;
	int				objects_count;
	int				enemies_count;
	int				ghosts_eaten;
	int				afterdeath;
	t_img			pacman_logo;
}	t_game;

# include "prototypes.h"

#endif
