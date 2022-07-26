/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:34 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/10 18:24:18 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

t_rgb	put_pixel_on_pixel(t_rgb *dst, t_rgb *src)
{
	if (src->a == 0)
		*dst = *src;
	else if (src->a != 0xFF)
	{
		dst->r += ((src->r - dst->r) * src->a) / 0xFF;
		dst->g += ((src->g - dst->g) * src->a) / 0xFF;
		dst->b += ((src->b - dst->b) * src->a) / 0xFF;
	}
	return (*dst);
}

void	put_image_to_image(t_img *dst, t_vector pos, t_img *src)
{
	const int	x = ft_max(-pos.x, 0) - 1;
	int			xcounter;
	int			ycounter;

	ycounter = ft_max(-pos.y, 0) - 1;
	while (++ycounter < src->size.y && ycounter < dst->size.y - pos.y)
	{
		xcounter = x;
		while (++xcounter < src->size.x && xcounter < dst->size.x - pos.x)
		{
			put_pixel_on_pixel((t_rgb *)dst->addr + (pos.y + ycounter)
				* dst->size.x + pos.x + xcounter,
				(t_rgb *)src->addr + ycounter * src->size.x + xcounter);
		}
	}
}

int	put_char_to_screen(t_texture *font, t_img *img, t_text *text, int font_size)
{
	if (font[ft_toupper(*text->text) - FONT_OFFSET].img)
	{
		put_downscaled_image(img, text,
			((t_img *)font[ft_toupper(*text->text) - FONT_OFFSET].img->content),
			FONT_SIZE / font_size);
		return (1);
	}
	return (1);
}

void	put_text_to_screen(t_texture *font,
	t_img *img, t_text *text, int font_size)
{
	char	*tmp;

	tmp = text->text;
	while (*text->text)
	{
		text->pos.x += put_char_to_screen(font, img, text, font_size)
			* font_size;
		++text->text;
	}
	text->text = tmp;
}

void	put_text_to_screen_layout(t_texture *font,
	t_img *img, t_text *text, int font_size)
{
	t_vector	pos;

	pos = text->pos;
	if (text->layout & VCenter)
		text->pos.y -= font_size / 2;
	else if (text->layout & VBottom)
		text->pos.y -= font_size;
	if (text->layout & HCenter)
		text->pos.x -= (ft_strlen(text->text) * font_size) / 2;
	else if (text->layout & HRight)
		text->pos.x -= (ft_strlen(text->text) * font_size);
	put_text_to_screen(font, img, text, font_size);
	text->pos = pos;
}
