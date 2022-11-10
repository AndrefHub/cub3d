/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:44:31 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/10 18:49:14 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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

typedef struct node
{
	t_vector	pos;	
	short		g;
	short		h;
	struct node	*parent;
}	t_astar_node;

typedef t_astar_node		t_node;

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
	t_texture		object[MAX_OBJECTS];
	t_texture		font[MAX_FONT_CHARS];
	t_texture		floor;
	t_texture		ceiling;
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
	char			*map_file;
	t_list			*(*enemy_algorithms[MAX_ENEMIES])(void *, void *);
}				t_map;

typedef struct ray
{
	t_fvector	unit;
	t_fvector	dir;
	t_vector	map_tile;
	t_fvector	len;
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
	int			type;

}				t_object;

typedef struct s_hud_entry
{
	int		value_numeric;
	char	*title;
	char	*value;
	short	title_size;
	short	value_size;
}				t_hud_entry;

typedef struct s_parse_info
{
	char		*chars;
	char		*prefix;
	t_texture	*arr;
	int			size;
}	t_parse_info;

typedef struct s_lb_entry
{
	char	*name;
	int		score_num;
	char	*score;
}	t_lb_entry;

typedef struct s_button
{
	t_vector	pos;
	t_vector	size;
	t_text		text;
	int			background_color;
	int			selected;
	int			pressed;
	int			released;
	int			(*draw_button)(void *, struct s_button *);
	int			(*on_selected)(void *, struct s_button *);
	int			(*on_pressed)(void *, struct s_button *);
	int			(*on_released)(void *, struct s_button *);
}	t_button;

typedef struct s_buttons
{
	t_button	buttons[PAUSE_ENTRIES];
	int			index;
}	t_button_list;

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
		float		dist;
		float		perp_dist;
		t_fvector	pos;
		int			side;
		t_fvector	ray_dir;
		t_vector	cell;
		char		dir;
		int			height;
		uint32_t	texture_id;
		float		texture_pos;
		int			color;
	}				*col;
	t_img			textures[MAX_WALL_CHARS];
	struct			s_audio
	{
		cs_context_t	*ctx;
		t_sound			sounds[MAX_SOUNDS];
	}					audio;
	struct	s_time
	{
		t_ull		startup;
		int			frames_to_move;
		t_ull		last;
		t_ull		fps_time;
		t_ull		pill_time;
	}				time;
	struct s_hud
	{
		int			font_size;
		t_hud_entry	fps;
		t_hud_entry	score;
		t_hud_entry	lives;
	}			hud;
	t_list			*leaderboard;
	char			*macos_chars;
	t_lb_entry		*player_lb_data;
	int				panic_mode;
	int				input_mode;
	char			*death_message;
	char			*place;
	int				objects_count;
	int				enemies_count;
	int				ghosts_eaten;
	int				afterdeath;
	char			*lb_filename;
	void			(*scene_funcs[MAX_MODES])(void *);
	int				(*input_funcs[MAX_MODES])(int, struct game *);
	void			(*death_func)(struct game *);
	t_button_list	pause;
	t_img			pacman_logo;
	t_ull			start_game_time;
	int				index_before_controls;
}	t_game;

typedef struct s_enemy
{
	t_object	*object;
	t_fvector	delta;
	t_ull		last_attack_time;
	t_fvector	starting_pos;
	t_list		*path;
	t_list		*(*pathfinding_algorithm)(t_game *, struct s_enemy *);
	t_sound		sound;
	int			panic_mode;
}				t_enemy;

#endif
