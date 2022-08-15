#include "../inc/cub3d.h"

bool	key_pressed(t_game *game, int key)
{
	return (game->key.k[key]);
}

int	close_hook(t_game *game)
{
	mlx_clear_window(game->mlx.id, game->mlx.window);
	mlx_destroy_window(game->mlx.id, game->mlx.window);
	exit(0);
	return (0);
}

int	key_hook_press(int key, t_game *game)
{
	if (key >= (int) sizeof(game->key) || key < -256)
		return (1);
	if (key == ESC_KEY)
		close_hook(game);
	if (key == M_KEY)
	{
		game->show_map = !game->show_map;
		return (0);
	}
	game->key.k[key] = true;
	return (0);
}

void	check_borders(t_game *game)
{
	char	tile;

	tile = game->grid[(int) game->player.pos.y][(int) game->player.pos.x];

	if (tile != '0')
	{
		if (game->player.pos.x - (int) game->player.pos.x < game->player.pos.y - (int) game->player.pos.y)
		{
			game->player.pos.x += 0.01f;
		}
		else
		{
			game->player.pos.y += 0.01f;
		}
	}
}

void	check_restrictions(t_game *game)
{
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
//	check_borders(game);
}

void	player_controll(t_game *game)
{
	if (key_pressed(game,W_KEY))
	{
		game->player.pos.x += game->player.delta.x;
		game->player.pos.y += game->player.delta.y;
	}
	if (key_pressed(game,S_KEY))
	{
		game->player.pos.x -= game->player.delta.x;
		game->player.pos.y -= game->player.delta.y;
	}
	if (key_pressed(game,D_KEY))
	{
		game->player.angle += PL_ROT_SPEED;
		game->player.delta.x = cosf(game->player.angle) * PL_SPEED;
		game->player.delta.y = sinf(game->player.angle) * PL_SPEED;
	}
	if (key_pressed(game,A_KEY))
	{
		game->player.angle -= PL_ROT_SPEED;
		game->player.delta.x = cosf(game->player.angle) * PL_SPEED;
		game->player.delta.y = sinf(game->player.angle) * PL_SPEED;
	}
	check_restrictions(game);
}

int	key_hook_release(int key, t_game *game)
{
	if (key >= (int) sizeof(game->key) || key < -256)
		return (1);
	game->key.k[key] = false;
	return (0);
}

int	game_loop(t_game *game)
{
	static clock_t	cur_time;
	static int		fps;

	player_controll(game);
	img_clear_rgb(&game->img, 0x808080);
//	draw_player(game);
	draw_rays(game);
	draw_3D(game);
//	draw_line(&game->img, (t_vector) {0, 0}, (t_vector) {WIN_WIDTH, WIN_HEIGHT - 54}, 0xABCDEF);
//	draw_line(&game->img, (t_vector) {WIN_WIDTH, 0}, (t_vector) {0, WIN_HEIGHT - 54}, 0xABCDEF);

	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img, 0, 0);
	if (game->show_map)
		draw_map(game);

	if (clock() != cur_time)
		fps = CLOCKS_PER_SEC / (clock() - cur_time);
	game->fps = fps;
	cur_time = clock();
	mlx_string_put(game->mlx.id, game->mlx.window, 0, 15, 0x00FFFFFF, \
		(char []){'0' + fps / 100, '0' + fps / 10 % 10, '0' + fps % 10, '\0'});
	return (0);
}