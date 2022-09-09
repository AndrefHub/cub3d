#include "../inc_bonus/cub3d_bonus.h"

#ifdef __APPLE__

void	mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	(void)mlx_ptr;
	mlx_mouse_get_pos(win_ptr, x, y);
}

void	mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	(void)mlx_ptr;
	mlx_mouse_move(win_ptr, x, y);
}

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

void	mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	mlx_mouse_get_pos(mlx_ptr, win_ptr, x, y);
}

void	mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	mlx_mouse_move(mlx_ptr, win_ptr, x, y);
}

void	mouse_show(void *mlx_ptr, void *win_ptr)
{
	mlx_mouse_show(mlx_ptr, win_ptr);
}

void	mouse_hide(void *mlx_ptr, void *win_ptr)
{
	mlx_mouse_hide(mlx_ptr, win_ptr);
}

#endif