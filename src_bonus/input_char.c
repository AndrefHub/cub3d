/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:49 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:49:51 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
