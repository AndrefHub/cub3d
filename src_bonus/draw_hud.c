/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:48:05 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:48:06 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

char	*set_lives(t_hud_entry *entry)
{
	int	counter;

	counter = -1;
	while (++counter < entry->value_numeric)
	{
		entry->value[counter] = '[';
	}
	return (entry->value);
}

// void	put_lives_value(t_game *game, t_hud_entry *entry)
// {

// }

void	draw_hud_entry(t_game *game, t_hud_entry *entry, int y)
{
	t_vector		text_pos;

	text_pos = (t_vector){game->mlx.win_size.x - (game->mlx.win_size.x
			- game->img.size.x) / 2 + ((game->mlx.win_size.x
				- game->img.size.x) / 2) / 1.75, game->hud.font_size * y};
	ft_bzero(entry->value, entry->value_size);
	put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
	{entry->title, (t_vector){text_pos.x, text_pos.y},
		VTop | HCenter, 0xDFEFEF}, game->hud.font_size);
	if (!ft_strncmp(entry->title, "lives:", entry->title_size))
	{
		set_lives(entry);
		put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
		{entry->value, (t_vector){text_pos.x - 3 * game->hud.font_size,
			text_pos.y + game->hud.font_size * 1.5f}, VTop | HLeft,
			PACMAN_COLOR}, game->hud.font_size * 1.5f);
	}
	else
	{
		ft_put_itoa(entry->value, entry->value_numeric);
		put_text_to_screen_layout(game->map->font, &game->hud_img, &(t_text)
		{entry->value, (t_vector){text_pos.x, text_pos.y + game->hud.font_size
			* 1.5f}, VTop | HCenter, 0xDFEFEF}, game->hud.font_size);
	}
}

void	draw_hud(t_game *game)
{
	int	y;

	y = 1;
	put_image_to_image(&game->hud_img, (t_vector){0, 0}, &game->hud_texture);
	if (game->hud.fps.value_numeric > 999)
		game->hud.fps.value_numeric = 999;
	draw_hud_entry(game, &game->hud.fps, ++y * 3);
	draw_hud_entry(game, &game->hud.score, ++y * 3);
	draw_hud_entry(game, &game->hud.lives, ++y * 3);
}
