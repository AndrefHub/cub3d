#include "../inc_bonus/cub3d_bonus.h"

void	put_image_to_image(t_img *dst, t_vector pos, t_img *src)
{
	int	xcounter;
	int	ycounter;
	
	ycounter = -1;
	while (++ycounter < src->size.y)
	{
		xcounter = -1;
		while (++xcounter < src->size.x)
		{
			put_pixel(dst, (t_vector){pos.x + xcounter, pos.y + ycounter},
				src->addr[ycounter * src->size.x + xcounter]);
		}
	}
}

int	put_char_to_screen(t_game *game, char c, t_vector pos, int divisor)
{
	if (game->map->font[ft_toupper(c) - FONT_OFFSET].img)
	{
		put_downscaled_image(&game->img, pos, ((t_img *)game->map->font
			[ft_toupper(c) - FONT_OFFSET].img->content), divisor);
		return (1);
		// put_image_to_image(&game->img, pos, ((t_img *)game->map->font
		// 	[ft_toupper(c) - FONT_OFFSET].img->content));
		// mlx_put_image_to_window(game->mlx.id, game->mlx.window, 
		// 	((t_img *)game->map->font[ft_toupper(c) - FONT_OFFSET].img->content)->mlx_img, 
		// 	pos.x, pos.y);
	}
	return (0);
}

void	put_text_to_screen(t_game *game, char *text, t_vector pos, int divisor)
{
	while (*text)
	{
		pos.x += put_char_to_screen(game, *text, pos, divisor) * FONT_SIZE / divisor;
		++text;
	}
}

void	put_text_to_screen_layout(t_game *game, t_text *text, int divisor)
{
	if (text->layout & VCenter)
		text->pos.y -= FONT_SIZE / (divisor * 2);
	else if (text->layout & VBottom)
		text->pos.y -= FONT_SIZE / divisor;
	if (text->layout & HCenter)
		text->pos.x -= (ft_strlen(text->text) * (FONT_SIZE / divisor)) / 2;
	else if (text->layout & HRight)
		text->pos.x -= (ft_strlen(text->text) * (FONT_SIZE / divisor));
	put_text_to_screen(game, text->text, text->pos, divisor);
}