/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:48:45 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 19:17:31 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	check_aliveness(t_game *game)
{
	if (game->player.health <= 0)
	{
		if (game->hud.lives.value_numeric <= 0)
			game->death_func = draw_afterdeath_animation;
		set_game_input_mode(game, WIN_SCREEN_MODE);
	}
}

int	edibles_eaten(t_game *game)
{
	return (!(game->objects_count - game->enemies_count));
}

void	change_all_enemies_cry_paused(t_game *game, int paused)
{
	t_list	*enemies;
	t_enemy	*enemy;

	enemies = game->map->enemies;
	while (enemies)
	{
		enemy = enemies->content;
		if (enemy->sound.play)
			enemy->sound.play->paused = paused;
		enemies = enemies->next;
	}
}

void	pause_game_actions(t_game *game)
{
	game->show_map = 0;
	change_all_enemies_cry_paused(game, 1);
}

void	put_ended_game_image(t_game *game)
{
	fill_img_color(&game->img, 0x0);
	if (game->input_mode == LEADERBOARD_MODE)
		leaderboard_message(game);
	else if (game->input_mode == WIN_SCREEN_MODE && edibles_eaten(game))
		win_message(game, "You\'re winner!", 0xFFD700);
	else
		win_message(game, "game over", 0x980000);
	put_frame(game);
}
