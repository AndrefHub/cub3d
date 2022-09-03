#include "../inc/cub3d.h"
#include <unistd.h>
#ifdef __APPLE__

static inline void	mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	(void)mlx_ptr;
	mlx_mouse_get_pos(win_ptr, x, y);
}

static inline void	mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	(void)mlx_ptr;
	mlx_mouse_move(win_ptr, x, y);
}

static inline void	mouse_show(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	mlx_mouse_show();
}

static inline void	mouse_hide(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	mlx_mouse_hide();
}

#else

static inline void	mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	mlx_mouse_get_pos(mlx_ptr, win_ptr, x, y);
}

static inline void	mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	mlx_mouse_move(mlx_ptr, win_ptr, x, y);
}

static inline void	mouse_show(void *mlx_ptr, void *win_ptr)
{
	mlx_mouse_show(mlx_ptr, win_ptr);
}

static inline void	mouse_hide(void *mlx_ptr, void *win_ptr)
{
	mlx_mouse_hide(mlx_ptr, win_ptr);
}

#endif

void	check_borders(t_game *game)
{
	char	tile;

	tile = game->grid[(int) game->player.pos.y / MAP_GRID_SIZE][(int) game->player.pos.x / MAP_GRID_SIZE];
	if (is_wall(tile))
	{
		if ((game->player.pos.x - (int ) game->player.pos.x) - (game->player.pos.y - (int ) game->player.pos.y) > 0)
			game->player.pos.x -= game->player.delta.x;
		else
			game->player.pos.y -= game->player.delta.y;
	}
}

void	check_restrictions(t_game *game)
{
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	if (game->player.pos.x > game->map->map_size.x * MAP_GRID_SIZE)
		game->player.pos.x -= MAP_GRID_SIZE;
	if (game->player.pos.x < 0)
		game->player.pos.x += MAP_GRID_SIZE;
	if (game->player.pos.y > game->map->map_size.y * MAP_GRID_SIZE)
		game->player.pos.y -= MAP_GRID_SIZE;
	if (game->player.pos.y < 0)
		game->player.pos.y += MAP_GRID_SIZE;
	check_borders(game);
}

int	float_sign(float f)
{
	return (1 - (f == 0.) - 2 * (f < 0.));
}

void	update_last_collision(t_game *game)
{
	game->map->last_collision.x = game->player.pos.x;
	game->map->last_collision.y = game->player.pos.y;
}

void	move_radius_check(t_game *game, float x_delta, float y_delta, int *collision)
{
	if (!is_wall(game->map->map[(int)game->player.pos.y / MAP_GRID_SIZE]
		[(int)(game->player.pos.x + x_delta + float_sign(x_delta) * PL_RADIUS) / MAP_GRID_SIZE]))
		game->player.pos.x += x_delta;
	else
	{
		if (game->map->last_collision.x != game->player.pos.x && game->map->last_collision.y != game->player.pos.y)
			++(*collision);
		update_last_collision(game);
	}
	if (!is_wall(game->map->map[(int)(game->player.pos.y + y_delta + float_sign(y_delta) * PL_RADIUS) / MAP_GRID_SIZE]
		[(int)game->player.pos.x / MAP_GRID_SIZE]))
		game->player.pos.y += y_delta;
	else
	{
		if (game->map->last_collision.x != game->player.pos.x && game->map->last_collision.y != game->player.pos.y)
			++(*collision);
		update_last_collision(game);
	}
}

void	open_door(t_game *game)
{
	const int	x = (int)game->player.pos.x / MAP_GRID_SIZE;
	const int	y = (int)game->player.pos.y / MAP_GRID_SIZE;
	const float	angle = game->player.angle;
	char		*to_change;
	
	to_change = NULL;
	if (PI / 4 <= angle && angle <= 3 * PI / 4 && ft_tolower(game->grid
		[y - 1][x]) == 'd')
		to_change = game->grid[y - 1] + x;
	else if (3 * PI / 4 <= angle && angle <= 5 * PI / 4 && ft_tolower(game->grid
		[y][x - 1]) == 'd')
		to_change = game->grid[y] + x - 1;
	else if (5 * PI / 4 <= angle && angle <= 7 * PI / 4 && ft_tolower(game->grid
		[y + 1][x]) == 'd')
		to_change = game->grid[y + 1] + x;
	else if ((7 * PI / 4 <= angle || angle <= PI / 4) && ft_tolower(game->grid
		[y][x + 1]) == 'd')
		to_change = game->grid[y] + x + 1;
	if (to_change && *to_change == 'd')
		*to_change = 'D';
	else if (to_change && *to_change == 'D')
		*to_change = 'd';
	ft_putendl_fd(to_change, 1);
}

void	player_controll(t_game *game)
{
	int collision = 0;

	if (game->key.mouse == true)
	{
		mouse_get_pos(game->mlx.id, game->mlx.window, &game->key.mpos.x,&game->key.mpos.y);
		game->key.mdir.x = game->key.mpos.x - game->img.size.x / 2;
		game->key.mdir.y = game->key.mpos.y - game->img.size.y / 2;
		mouse_move(game->mlx.id, game->mlx.window, game->img.size.x / 2, game->img.size.y / 2);
		game->player.angle += (float) game->key.mdir.x * PL_ROT_MOUSE_SPEED * 2;
		game->player.delta.x = cosf(game->player.angle) * PL_SPEED;
		game->player.delta.y = sinf(game->player.angle) * PL_SPEED;
	}
	if (key_pressed(game, W_KEY))
		move_radius_check(game, game->player.delta.x, game->player.delta.y, &collision);
	if (key_pressed(game, S_KEY))
		move_radius_check(game, -game->player.delta.x, -game->player.delta.y, &collision);
	if (key_pressed(game, D_KEY))
		move_radius_check(game, -game->player.delta.y, game->player.delta.x, &collision);
	if (key_pressed(game, A_KEY))
		move_radius_check(game, game->player.delta.y, -game->player.delta.x, &collision);
	if (key_pressed(game, RIGHT_KEY))
	{
		game->player.angle += PL_ROT_KEY_SPEED;
		game->player.delta.x = cosf(game->player.angle) * PL_SPEED;
		game->player.delta.y = sinf(game->player.angle) * PL_SPEED;
	}
	if (key_pressed(game, LEFT_KEY))
	{
		game->player.angle -= PL_ROT_KEY_SPEED;
		game->player.delta.x = cosf(game->player.angle) * PL_SPEED;
		game->player.delta.y = sinf(game->player.angle) * PL_SPEED;
	}
	if (collision)
	{
		cs_play_sound(game->audio.ctx, game->audio.bonk.def);
		update_last_collision(game);
	}
	check_restrictions(game);
}

void	change_textures(t_game *game)
{
	const int	clocks_per_frame = 1000 / FRAMERATE;
	int	index;
	int	frames_to_move;
	int	counter;
	static int f = 0;
	static int s = 0;

	frames_to_move = (get_time() - game->time.startup) / clocks_per_frame \
		- (game->time.last - game->time.startup) / clocks_per_frame;
	game->time.last = get_time();
	if (frames_to_move)
	{
		index = -1;
		while (++index < MAX_TEXTURES)
		{
			counter = -1;
			while (++counter < frames_to_move)
				game->map->img_list[index] = game->map->img_list[index]->next;
			game->textures[index] = *(t_img *)game->map->img_list[index]->content;	
		}
	}
	f += frames_to_move;
	++s;
	printf("%f ", ((double)f) / s);
}

int	game_loop(t_game *game)
{
	player_controll(game);
	img_clear_rgb(&game->img, 0x808080);
//	draw_player(game);
	cast_rays(game);
	draw_walls(game);
	draw_aim(game);

	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img, 0, 0);
	if (game->show_map)
		draw_map(game);
	draw_fps(game);
	change_textures(game);
	return (0);
}
