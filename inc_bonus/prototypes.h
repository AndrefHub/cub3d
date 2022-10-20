#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// after_death_anim.c //

int		get_rand_color(void);
void	draw_afterdeath_animation(t_game *game);

// border_checking.c //

int		check_enclosure(t_map *map, t_vector vec);
int		get_map_width(const char **map);
int		is_map_enclosed(t_map *map);

// button_functions.c //

int		default_button_func(void *v, struct s_button *b);
int		button_actions(t_game *game, t_button *button);
int		button_pressed(t_game *game, t_button *button);
int		button_released(t_game *game, t_button *button);
int		button_selected(t_game *game, t_button *button);

// check_file.c //

int		check_file(int ac, char **av);

// controller.c //

void	change_objects_textures(t_game *game);
void	change_textures(t_game *game);
void	open_door(t_game *game);

// death_events.c //

char	*get_rank_str(char *str, int rank);
int		edibles_eaten(t_game *game);
t_text	*set_rank_color(t_text *text, int rank);
void	change_all_enemies_cry_paused(t_game *game, int paused);
void	check_aliveness(t_game *game);
void	leaderboard_message(t_game *game);
void	pause_game_actions(t_game *game);
void	player_death(t_game *game);
void	player_win(void *_game);
void	put_ended_game_image(t_game *game);
void	put_username_on_screen(t_game *game);
void	win_message(t_game *game, char *message, int color);

// demo_utils.c //

char	**charlist_to_matrix(t_list *list);

// downscale_image.c //

int		get_downscaled_color(t_img *img, int divisor, t_vector pos);
int		get_downscaled_colored_font(t_img *img, int divisor, t_vector pos,
			t_rgb color);
void	put_downscaled_image(t_img *dst, t_text *text, t_img *src, int divisor);

// draw_ceil_floor.c //

void	draw_ceil_floor_textured(t_game *game);

// draw_hud.c //

void	draw_hud(t_game *game);
void	draw_hud_entry(t_game *game, t_hud_entry *entry, int y);

// draw_map.c //

void	draw_enemies_on_map(t_game *game);
void	draw_map(t_game *game);
void	draw_objects_on_map(t_game *game);
void	draw_player_on_map(t_game *game);

// draw_objects.c //

int		object_comparator(t_object *obj1, t_object *obj2);
void	calculate_object_params(t_game *game, t_object *object);
void	draw_game_objects(t_game *game);
void	draw_object_scaled(t_game *game, t_object *object);
void	update_distance(t_game *game);

// draw_walls.c //

void	draw_wall_scaled(t_img *img, const t_img *texture,
			const struct s_column *column, int x, t_game *game);
void	draw_walls(t_game *game);

// drawing.c //

void	draw_aim(t_game *game);
void	draw_line(t_img *img, t_vector p1, t_vector p2, int color);
void	draw_player(t_game *game);
void	draw_rectangle_fill(t_img *img, t_vector top_left, t_vector size,
			int color);
void	draw_square_fill(t_img *img, t_vector top_left, int size, int color);
void	fill_ceiling_color(t_img *img, int color, int horizon);
void	fill_floor_color(t_img *img, int color, int horizon);
void	fill_img_color(t_img *img, int color);
void	put_pixel(t_img *img, t_vector point, int color);

// enemy_actions.c //

float	calculate_angle(t_fvector p, t_fvector e);
void	enemy_attack(t_game *game, t_enemy *enemy);
void	enemy_calculate_frame_movement(t_node *node, t_enemy *enemy);
void	enemy_check_collision(t_game *game, t_enemy *enemy);
void	enemy_move(t_game *game);
void	enemy_move_along_path(t_game *game, t_enemy *enemy);
void	reset_panic_mode(void *en);
void	update_path(t_game *game, t_enemy *enemy, t_list **path);

// enemy_astar.c //

int		heuristic_cost(t_vector lhs, t_vector rhs);
int		node_comparator(t_node *lhs, t_node *rhs);
int		pos_equals(void *lhs, void *rhs);
t_list	*astar(t_game *game, t_vector enemy, t_vector player);
t_list	*ft_lstfind(t_list *closed, void *val, int equals(void *, void *));
t_list	*get_first_n_nodes(t_list *lst, int n);
t_node	*ft_nodenew(t_node *data);
void	add_all_neighbours(t_game *game, t_list **open, t_list *closed,
			t_node *node, t_vector player);

// enemy_move.c //

t_list	*pathfinding_algo_straight(t_game *game, t_enemy *enemy);

// file_parser.c //

int		cmp_lb_entry(void *lhs, void *rhs);
int		cmp_number(int lhs, int rhs);
int		cmp_string_number(void *lhs, void *rhs);
t_list	*get_leaderboard(char *filename);

// find_objects.c //

int		find_player(t_map *map, char *line, t_list *lst);
int		ft_strchr_int(char *line, int chr);
int		ft_strchr_int_arr(char *line, char *chr);
int		set_player(t_map *map, t_list *lst, char *line, char *orient);
void	find_enemy(t_list **lst, t_object *object);
void	find_objects(t_map *map);

// free_game.c //

void	free_sound(t_game *game);
void	free_texture_lists(t_game *game);

// ft_lstsort.c //

void	ft_lstsort(t_list **lst, int (*cmp)());

// ft_utils.c //

char	*get_full_texture_path(char *line, int flag);
float	distancef(t_fvector *vector1, t_fvector *vector2);
int		ft_arraylen(void **arr);
int		is_line_empty(char *line);
int		is_space(char c);
t_img	initialize_img(t_img *img, void *mlx_ptr, int width, int height);
t_map	*create_empty_map(void);
void	error_exit(t_game *game, int return_value, char *message);
void	print_map_debug(t_map *map);

// game_loop.c //

float	ftorange(float val, float border);
int		game_loop(t_scene *scene);
void	death_game_scene(t_game *game);
void	pac_game_scene(t_game *game);
void	pause_game_scene(t_game *game);
void	put_frame(t_game *game);
void	update_volume(t_game *game);

// game_sound.c //

void	copy_sound(t_sound *sound, t_sound *src);
void	init_main_game_sound(t_game *game);
void	set_game_events_sounds(struct s_audio *audio, char **sounds);
void	set_sound(t_sound *sound, char *filename);

// game_textures.c //

void	draw_texture_set(t_game *game, struct s_column *column);
void	import_texture_to_img(t_game *game, t_img *img, char *filename,
			int size_x, int size_y);
void	initialize_sprites(t_game *game, int size, t_texture *sprites_list,
			int t_size);
void	initialize_wall_textures(t_game *game);
void	skip_transparent_background(t_img *img);

// hooks.c //

bool	key_pressed(t_game *game, int key);
int		close_hook(t_game *game);
int		key_hook_press(int key, t_game *game);
int		key_hook_release(int key, t_game *game);
int		mouse_hook_press(int button, int x, int y, t_game *game);
int		mouse_hook_release(int button, int x, int y, t_game *game);

// image_manip.c //

void	dim_image(t_img *img, int img_size, t_rgb *color);
void	dim_screen(t_game *game, int i);

// init_utils.c //

void	init_hud(struct s_hud *hud);
void	init_hud_entry(t_hud_entry *entry, char *title);

// input_char.c //

void	input_char(int key, char *username, char *charset);

// input_funcs.c //

int		game_input_mode(int key, t_game *game);
int		pause_mode(int key, t_game *game);
int		username_input_mode(int key, t_game *game);
int		win_screen_mode(int key, t_game *game);
int		controls_mode(int key, t_game *game);

// input_manip.c //

char	*crop_prefix(char *line, char *prefix);
char	*ft_strcat_delim(char *first, char delim, char *second);
char	*skip_empty_lines(int fd);
int		convert_to_rgb(char *line);

// is_checks.c //

int		is_edible(char c);
int		is_enemy(char c);
int		is_object(char c);
int		is_wall(char c);

// leaderboard_funcs.c //

void	ft_lst_insert(t_list **lst, t_list *to_insert, int cmp(void *, void *));
void	print_lb(t_list *lb);
void	update_leaderboard_file(t_game *game);

// main.c //

int		main(int ac, char **av);

// mlx_adapter.c //

void	mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);
void	mouse_hide(void *mlx_ptr, void *win_ptr);
void	mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
void	mouse_show(void *mlx_ptr, void *win_ptr);

// parsing.c //

char	**lst_to_array(t_list *tmp);
int		get_string_index(char *str, char c);
t_map	*parse_file(int ac, char **av);
void	empty_func(void *ptr);
void	parse_map(t_map *map, int fd);

// parsing_font.c //

void	parse_font(t_map *map, int fd, char **line);

// parsing_textures.c //

void	parse_assets(t_map *map, int fd);
void	parse_config(t_map *map, int fd, char **line);
void	parse_enemies(t_map *map, int fd, char **line);
void	parse_sounds(t_map *map, int fd, char **line);
void	parse_texture(int fd, char **line, t_parse_info info);
void	parse_texture_list_array(int fd, char **line, t_parse_info info);
void	parse_walls(t_map *map, int fd, char **line);

// parsing_utils.c //

int		ft_strrchr_int(const char *line, int chr);
int		ft_strrchr_int_arr(const char *line, char *chr);
t_map	*free_map(t_map *map);
void	convert_spaces_to_zeros(t_map *map);
void	map_to_rectangle(t_map *map);

// pause_menu.c //

void	print_pause_menu_entries(t_game *game);
void	show_button(t_img *img, t_texture *font, t_button *button);
void	show_buttons(t_img *img, t_texture *font, t_button *buttons, int size);
int		exit_button_func(void *game, t_button *button);
int		selected_button_func(void *__game, t_button *button);

// player_controller.c //

void	mouse_controller(t_game *game);
void	movement_controller(t_game *game, int *collision);
void	player_controll(t_game *game);
void	player_delta_calculation(struct s_player *player);
void	rotation_by_key_controller(t_game *game);

// player_eating.c //

void	eat_by_coords(t_game *game, t_vector pos);
void	ft_lstdelbyaddr(t_list **lst, t_list *to_del, void (*del)(void *));
void	pill_eaten(t_game *game);
void	player_eat(t_game *game);
void	set_panic_mode(t_game *game);

// player_movement.c //

void	check_borders(t_game *game, struct s_player *object);
void	check_borders_enemy(t_game *game, t_object *object);
void	check_restrictions(t_game *game);
void	move_radius_check(t_game *game, float x_delta, float y_delta,
			int *collision);
void	update_last_collision(t_game *game);

// put_text.c //

int		put_char_to_screen(t_texture *font, t_img *img, t_text *text,
			int font_size);
t_rgb	put_pixel_on_pixel(t_rgb *dst, t_rgb *src);
void	put_image_to_image(t_img *dst, t_vector pos, t_img *src);
void	put_text_to_screen(t_texture *font, t_img *img, t_text *text,
			int font_size);
void	put_text_to_screen_layout(t_texture *font, t_img *img, t_text *text,
			int font_size);

// ray_casting.c //

float	interception_distance(t_game *game, t_ray *ray);
t_ray	ray_initialize(t_game *game, t_fvector ray_dir);
void	cast_rays(t_game *game);
void	get_interception(t_game *game, t_fvector ray_dir, int i);
void	initialize_columns(t_game *game, t_ray *ray, float distance,
			int i, float ray_angle);

// respawn.c //

int		player_respawn(t_game *game);
void	reset_enemy_position(void *enemy);
void	reset_positions(t_game *game);

// start_game.c //

char	*get_lb_name(char *filename);
int		init_game(t_map *map);
void	clear_font_outline(t_game *game);
void	init_buttons(t_game *game);
void	init_default_button(t_button *button, int size, char *text);
void	init_input_funcs(t_game *game);
void	initialize_game_hud(t_game *game);
void	initialize_game_objects(t_game *game);
void	initialize_game_parameters(t_game *game);
void	initialize_mlx_parameters(t_game *game);
void	initialize_player(t_game *game);
void	play_sounds(t_game *game);
void	set_enemy_sounds(t_game *game);
void	set_input_mode_chars(t_game *game);
void	start_game(t_game *game);

// time_funcs.c //

t_ull	get_time(void);
t_ull	get_time_hp(void);
void	init_time(t_game *game);
void	update_time(t_game *game);
void	wait_milliseconds(int milliseconds);

// vector_utils.c //

float	fvector_distance(t_fvector lhs, t_fvector rhs);
int		float_sign(float f);

#endif
