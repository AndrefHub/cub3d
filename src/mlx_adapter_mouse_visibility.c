/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_adapter_mouse_visibility.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:47:11 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/09 18:47:12 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#ifdef __APPLE__

void	mouse_show(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	mlx_mouse_show();
}

void	mouse_hide(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	mlx_mouse_hide();
}

#else

void	mouse_show(void *mlx_ptr, void *win_ptr)
{
	mlx_mouse_show(mlx_ptr, win_ptr);
}

void	mouse_hide(void *mlx_ptr, void *win_ptr)
{
	mlx_mouse_hide(mlx_ptr, win_ptr);
}

#endif