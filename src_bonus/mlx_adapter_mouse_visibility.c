/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_adapter_mouse_visibility.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:50:08 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:50:10 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

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
