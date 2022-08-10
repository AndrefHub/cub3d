#include "../inc/cub3d.h"

int	close_hook(t_game *game)
{
	mlx_clear_window(game->mlx.id, game->mlx.window);
	mlx_destroy_window(game->mlx.id, game->mlx.window);
	exit(0);
	return (0);
}

int	key_hook_press(int key, t_game *game)
{
	if (key == ESC_KEY)
		close_hook(game);
	if (key == W_KEY) {
		game->player.pos.x += game->player.delta.x;
		game->player.pos.y += game->player.delta.y;
	}
	if (key == S_KEY)
	{
		game->player.pos.x -= game->player.delta.x;
		game->player.pos.y -= game->player.delta.y;
	}
	if (key == D_KEY)
	{
		game->player.angle += 0.1f;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		game->player.delta.x = cos(game->player.angle) * 5;
		game->player.delta.y = sin(game->player.angle) * 5;
	}
	if (key == A_KEY)
	{
		game->player.angle -= 0.1f;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		game->player.delta.x = cos(game->player.angle) * 5;
		game->player.delta.y = sin(game->player.angle) * 5;
	}
	return (0);
}



int	game_loop(t_game *game)
{
	game->frames++;
//	draw_line(&game->img, (t_vector) {0, 0}, (t_vector) {WIN_WIDTH, WIN_HEIGHT - 54}, 0xABCDEF);
//	draw_line(&game->img, (t_vector) {WIN_WIDTH, 0}, (t_vector) {0, WIN_HEIGHT - 54}, 0xABCDEF);
	img_clear_rgb(&game->img, 0x808080);
	draw_map(game);
	draw_player(game);

	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->img.mlx_img, 0, 0);
	return (0);
}