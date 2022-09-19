#include "../inc_bonus/cub3d_bonus.h"

t_rgb	put_pixel_on_pixel(t_rgb *dst, t_rgb *src)
{
	if (!src->a)
		*dst = *src;
	else if (src->a != 0xFF)
	{
		dst->r += ((src->r - dst->r) * src->a) / 0xFF;
		dst->g += ((src->g - dst->g) * src->a) / 0xFF;
		dst->b += ((src->b - dst->b) * src->a) / 0xFF;
		// dst->r = ((dst->r * (0xFF - src->a)) + (src->r * src->a)) / 0xFF;
		// dst->g = ((dst->g * (0xFF - src->a)) + (src->g * src->a)) / 0xFF;
		// dst->b = ((dst->b * (0xFF - src->a)) + (src->b * src->a)) / 0xFF;
	}
	return (*dst);
}

void	put_image_to_image(t_img *dst, t_vector pos, t_img *src)
{
	const int x = ft_max(-pos.x, 0) - 1;
	int	xcounter;
	int	ycounter;
	
	ycounter = ft_max(-pos.y, 0) - 1;
	while (++ycounter < src->size.y && ycounter < dst->size.y - pos.y)
	{
		xcounter = x;
		while (++xcounter < src->size.x && xcounter < dst->size.x - pos.x)
		{
			put_pixel_on_pixel((t_rgb *)dst->addr + (pos.y + ycounter) * dst->size.x + pos.x
				+ xcounter, (t_rgb *)src->addr + ycounter * src->size.x + xcounter);
		}
	}
}

int	put_char_to_screen(t_game *game, char c, t_vector pos, int font_size)
{
	if (game->map->font[ft_toupper(c) - FONT_OFFSET].img)
	{
		put_downscaled_image(&game->hud, pos, ((t_img *)game->map->font
			[ft_toupper(c) - FONT_OFFSET].img->content), FONT_SIZE / font_size);
		return (1);
		// put_image_to_image(&game->img, pos, ((t_img *)game->map->font
		// 	[ft_toupper(c) - FONT_OFFSET].img->content));
		// mlx_put_image_to_window(game->mlx.id, game->mlx.window, 
		// 	((t_img *)game->map->font[ft_toupper(c) - FONT_OFFSET].img->content)->mlx_img, 
		// 	pos.x, pos.y);
	}
	return (0);
}

void	put_text_to_screen(t_game *game, char *text, t_vector pos, int font_size)
{
	while (*text)
	{
		pos.x += put_char_to_screen(game, *text, pos, font_size) * font_size;
		++text;
	}
}

void	put_text_to_screen_layout(t_game *game, t_text *text, int font_size)
{
	if (text->layout & VCenter)
		text->pos.y -= font_size / 2;
	else if (text->layout & VBottom)
		text->pos.y -= font_size;
	if (text->layout & HCenter)
		text->pos.x -= (ft_strlen(text->text) * font_size) / 2;
	else if (text->layout & HRight)
		text->pos.x -= (ft_strlen(text->text) * font_size);
	put_text_to_screen(game, text->text, text->pos, font_size);
}