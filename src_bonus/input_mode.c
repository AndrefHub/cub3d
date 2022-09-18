#include "../inc_bonus/cub3d_bonus.h"

#ifdef __APPLE__

void	input_char(int key, char *username, char *charset)
{
	if (0x0 <= key && (size_t)key < ft_strlen(charset))
	{
		if (ft_strlen(username) < 8)
			username[ft_strlen(username)] = charset[key];
	}
}

#else

void	input_char(int key, char *username, char *charset)
{
	if (FONT_OFFSET <= ft_toupper(key) && ft_toupper(key) < FONT_OFFSET + 0x40)
	{
		if (ft_strlen(username) < 8)
			username[ft_strlen(username)] = key;
		(void) charset;
	}
}

#endif

inline void	input_mode(int key, t_game *game)
{
	if (key == BACKSPACE) // Backspace
		game->username[ft_strlen(game->username) - 1] = '\0';
	else if (key == ENTER) // Enter, to add confirm action
		;
	else
		input_char(key, game->username, game->macos_chars);
}	
