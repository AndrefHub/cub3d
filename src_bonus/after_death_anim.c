/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_death_anim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:10 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:47:19 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	get_rand_color(void)
{
	const int	colors[] = {0xff0000, 0x00ff00, 0xffff00, 0x0000ff, 0xff00ff};

	return (colors[ft_rand() % 5]);
}

void	draw_afterdeath_inner_cycle(t_game *game, t_text *text, int font_size, int y_max)
{
	const int	len = (int)ft_strlen(game->macos_chars);
	t_vector	v;

	v.y = 0;
	while (v.y < game->img.size.y - font_size)
	{
		v.x = 0;
		while (v.x < game->img.size.x - font_size)
		{
			if (ft_rand() % 10 > 2 && ((v.y < (y_max + ((float)(ft_rand() % 5)
							/ 10.f) * game->img.size.y)) && v.y > y_max
				- ((float)(ft_rand() % 10) / 10.f) * game->img.size.y))
			{
				text->text = (char *)(game->macos_chars + (ft_rand() % len));
				text->pos = v;
				text->layout = 0;
				text->color = get_rand_color();
				draw_square_fill(&game->img, text->pos, font_size, 0x00000000);
				put_char_to_screen(game->map->font, &game->img,
					text, font_size);
			}
			v.x += font_size;
		}
		v.y += font_size;
	}
}

void	draw_afterdeath_animation(t_game *game)
{
	static int	y_max = 0;
	t_text		text;
	int			font_size;

	game->death_func = end_game_dim;
	font_size = game->hud.font_size * 0.6f - 1;
	if (y_max > game->img.size.y + font_size)
		return ;
	game->death_func = draw_afterdeath_animation;
	fill_ceiling_color(&game->img, 0x00000000, (game->img.size.y / 2) - y_max);
	draw_afterdeath_inner_cycle(game, &text, font_size, y_max);
	y_max += font_size;
	put_frame(game);
}
