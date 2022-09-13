#include "../inc_bonus/cub3d_bonus.h"

void	put_char_to_screen(t_game *game, char c, t_vector pos)
{
	if (game->map->font[ft_toupper(c) - FONT_OFFSET].img)
	{
		mlx_put_image_to_window(game->mlx.id, game->mlx.window, 
			((t_img *)game->map->font[ft_toupper(c) - FONT_OFFSET].img->content)->mlx_img, 
			pos.x, pos.y);
	}
}

void	put_text_to_screen(t_game *game, char *text, t_vector pos)
{
	while (*text)
	{
		put_char_to_screen(game, *text, pos);
		pos.x += FONT_SIZE;
		++text;
	}
}

void	put_text_to_screen_centered(t_game *game, char *text, t_vector pos)
{
	pos.y -= FONT_SIZE / 2;
	pos.x -= (ft_strlen(text) * FONT_SIZE) / 2;
	put_text_to_screen(game, text, pos);
}