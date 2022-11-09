#include "../inc/cub3d.h"

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

#else

void	mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	mlx_mouse_get_pos(mlx_ptr, win_ptr, x, y);
}

void	mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	mlx_mouse_move(mlx_ptr, win_ptr, x, y);
}

#endif