#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// src/border_checking.c //

int	check_enclosure(t_map *map, t_vector vec);
int	get_map_width(const char **map);
int	is_map_enclosed(t_map *map);

// src/check_file.c //

int	check_file(int ac, char **av);

// src/demo_utils.c //

char	**charlist_to_matrix(t_list *list);

// src/draw_ceil_floor.c //

void	draw_ceil_floor_textured(t_game *game);

// src/draw_map.c //

void	draw_enemies_on_map(t_game *game);
void	draw_map(t_game *game);
void	draw_objects_on_map(t_game *game);
void	draw_player_on_map(t_game *game);

// src/draw_walls.c //

void	draw_wall_scaled(t_img *img, const t_img *texture, t_vector v, t_game *game);
void	draw_walls(t_game *game);

// src/drawing.c //

void	draw_aim(t_game *game);
void	draw_line(t_img *img, t_vector p1, t_vector p2, int color);
void	draw_square_fill(t_img *img, t_vector top_left, int size, int color);

// src/drawing_utils.c //

void	fill_ceiling_color(t_img *img, int color, int horizon);
void	fill_floor_color(t_img *img, int color, int horizon);
void	fill_img_color(t_img *img, int color);
void	put_pixel(t_img *img, t_vector point, int color);

// src/find_objects.c //

int	find_player(t_map *map, char *line, t_list *lst);
int	set_player(t_map *map, t_list *lst, char *line, char *orient);

// src/ft_utils.c //

float	distancef(t_fvector *vector1, t_fvector *vector2);
int	ft_arraylen(void **arr);
int	ft_strchr_int(char *line, int chr);
int	is_line_empty(char *line);
int	is_space(char c);

// src/ft_utils_game.c //

t_map	*create_empty_map(void);
void	error_exit(t_game *game, int return_value, char *message);
t_img	initialize_img(t_img *img, void *mlx_ptr, int width, int height);

// src/game_loop.c //

int	game_loop(t_scene *scene);
void	put_frame(t_game *game);

// src/game_scenes.c //

void	pac_game_scene(t_game *game);

// src/game_textures.c //

void	draw_texture_set(t_game *game, struct s_column *column);
void	import_texture_to_img(t_game *game, t_img *img, char *filename, t_vector size);
void	initialize_sprites(t_game *game, int size, t_texture *sprites_list, int t_size);
void	initialize_wall_textures(t_game *game);
void	skip_transparent_background(t_img *img);

// src/get_screen_size.c //

void	get_screen_size(void *mlx_ptr, int *size_x, int *size_y);

// src/hooks.c //

int	close_hook(t_game *game);
int	key_hook_press(int key, t_game *game);
int	key_hook_release(int key, t_game *game);
int	mouse_hook_press(int button, int x, int y, t_game *game);
int	mouse_hook_release(int button, int x, int y, t_game *game);

// src/input_manip.c //

int	convert_to_rgb(char *line);
char	*crop_prefix(char *line, char *prefix);
char	*ft_strcat_delim(char *first, char delim, char *second);
char	*skip_empty_lines(int fd);

// src/is_checks.c //

int	is_wall(char c);

// src/key_pressed.c //

bool	key_pressed(t_game *game, int key);

// src/main.c //

int	main(int ac, char **av);

// src/mlx_adapter_mouse_position.c //

void	mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);
void	mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);

// src/mlx_adapter_mouse_visibility.c //

void	mouse_hide(void *mlx_ptr, void *win_ptr);
void	mouse_show(void *mlx_ptr, void *win_ptr);

// src/parsing.c //

void	empty_func(void *ptr);
int	get_string_index(char *str, char c);
char	**lst_to_array(t_list *tmp);
t_map	*parse_file(int ac, char **av);
void	parse_map(t_map *map, int fd);

// src/parsing_textures.c //

void	parse_assets(t_map *map, int fd);
char	*parse_texture(int fd, char **line, char *prefix);

// src/parsing_utils.c //

void	convert_spaces_to_zeros(t_map *map);
int	ft_strrchr_int(const char *line, int chr);
int	ft_strrchr_int_arr(const char *line, char *chr);
void	map_to_rectangle(t_map *map);

// src/player_controller.c //

void	mouse_controller(t_game *game);
void	movement_controller(t_game *game);
void	player_controll(t_game *game);
void	player_delta_calculation(struct s_player *player);
void	rotation_by_key_controller(t_game *game);

// src/player_movement.c //

void	check_borders(t_game *game, struct s_player *object);
void	check_restrictions(t_game *game);
void	move_radius_check(t_game *game, float x_delta, float y_delta);

// src/ray_casting.c //

float	calculate_angle(t_fvector p, t_fvector e);
void	cast_rays(t_game *game);
void	get_interception(t_game *game, t_fvector ray_dir, int i);
void	initialize_columns(t_game *game, t_ray *ray, float distance, int i, float ray_angle);
float	interception_distance(t_game *game, t_ray *ray);
t_ray	ray_initialize(t_game *game, t_fvector ray_dir);

// src/start_game.c //

int	init_game(t_map *map);
void	start_game(t_game *game);

// src/start_game_game_data.c //

void	*initialize_game_data(void *ptr);
void	initialize_player(t_game *game);
void	initialize_textures(t_game *game);

// src/start_game_title_screen.c //

void	initialize_game_hud(t_game *game);
void	initialize_game_parameters(t_game *game);
void	initialize_mlx_parameters(t_game *game);
void	initialize_start_game_variables(t_game *game);

// src/vector_utils.c //

int	float_sign(float f);
float	fvector_distance(t_fvector lhs, t_fvector rhs);

#endif
