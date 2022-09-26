#include "../inc_bonus/cub3d_bonus.h"

void	init_hud_entry(t_hud_entry *entry, char *title, int value_size)
{
	short	size;

	entry->value = 0; // not necessary after bzero
	entry->title_size = ft_strlen(title);
	entry->value_size = value_size;
	size = entry->value_size + entry->title_size + 1;
	entry->title = malloc(size);
	ft_bzero(entry->title, size);
	ft_strlcat(entry->title, title, entry->title_size + 1);
}

void	init_hud(struct s_hud *hud)
{
	init_hud_entry(&hud->fps, "fps:", 4);
	init_hud_entry(&hud->score, "score:", 7);
	init_hud_entry(&hud->lives, "lives:", 1);
	hud->lives.value = 3;
	init_hud_entry(&hud->health, "health:", 3);
	hud->health.value = 1;
}