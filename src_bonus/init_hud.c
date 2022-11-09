/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:48 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:49:49 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

void	init_hud_entry(t_hud_entry *entry, char *title)
{
	entry->value_numeric = 0;
	entry->title_size = ft_strlen(title);
	entry->value_size = 8;
	entry->value = malloc(entry->value_size + 1);
	ft_bzero(entry->value, entry->value_size + 1);
	entry->title = ft_strdup(title);
}

void	init_hud(struct s_hud *hud)
{
	init_hud_entry(&hud->fps, "fps:");
	init_hud_entry(&hud->score, "score:");
	init_hud_entry(&hud->lives, "lives:");
	hud->lives.value_numeric = 2;
}
