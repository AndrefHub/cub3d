#include "../inc_bonus/cub3d_bonus.h"

void	put_frame(t_game *game)
{
	put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x - game->img.size.x) / 2, 0}, &game->img);
	if (game->show_map)
	{
		draw_map(game);
		put_image_to_image(&game->hud_img, (t_vector){(game->mlx.win_size.x - game->img.size.x) / 2, 0}, &game->map->img);
	}
	mlx_put_image_to_window(game->mlx.id, game->mlx.window, game->hud_img.mlx_img,
							0, 0);
}

void	player_win(t_game *game)
{
	static int c = 0;

	if (!c)
	{
		printf("You\'re winner!");
		++c;
	}
	(void)game;
}

void	death_game_scene(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	draw_afterdeath_animation(game);
	if (game->afterdeath != 1)
	{
		player_death(game);
	}
	update_time(game);
}

void	pac_game_scene(t_game *game)
{
	fill_img_color(&game->hud_img, TRANSPARENT_COLOR);
	check_aliveness(game);
	player_controll(game);
	cast_rays(game);
	enemy_move(game);

	draw_ceil_floor_textured(game);
	draw_walls(game);
	draw_game_objects(game);

	draw_aim(game);

	draw_hud(game);
	put_frame(game);
	change_textures(game);
	update_time(game);
}

int	game_loop(t_scene *scene)
{
	scene->scene_func(scene->parameter);
	return (0);
}