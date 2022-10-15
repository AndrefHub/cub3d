#include "../inc_bonus/cub3d_bonus.h"

int		get_rand_color()
{
	const int colors[] = {0x00ff0000, 0x0000ff00, 0x00ffff00, 0x000000ff, 0x00ff00ff};

	return (colors[ft_rand() % 5]);
}

void	draw_afterdeath_animation(t_game *game)
{
	const int len = (int) ft_strlen(game->macos_chars);
	static int	y_max = 0;
	int	y;
	int	x;
	t_text text;
	int font_size;


	game->afterdeath = 0;
	font_size = game->hud.font_size * 0.9f;
	if (y_max > game->img.size.y + font_size)
		return;
	game->afterdeath = 1;
	fill_ceiling_color(&game->img, 0x00000000, (game->img.size.y / 2) - y_max);
	y = 0;
	while (y < game->img.size.y - font_size)
	{
		x = 0;
		while (x < game->img.size.x - font_size)
		{
			if (ft_rand() % 10 > 2
			&& ((y < (y_max + ((float) (ft_rand() % 5) / 10.f) * game->img.size.y))
			&& y > y_max - ((float) (ft_rand() % 10) / 10.f) * game->img.size.y))
			{
				text.text = (char *) (game->macos_chars + (ft_rand() % len));
				text.pos = (t_vector) {x, y};
				text.layout = 0;
				text.color = get_rand_color();
				draw_square_fill(&game->img, text.pos, font_size,
								 0x00000000);
				put_char_to_screen(game->map->font, &game->img, &text,
								   font_size);
			}
			x += font_size;
		}
		y += font_size;
	}
	y_max += font_size;
	put_frame(game);
	usleep(70000);
}