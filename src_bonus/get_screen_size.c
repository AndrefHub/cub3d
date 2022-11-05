#include "../inc_bonus/cub3d_bonus.h"

#ifdef __APPLE__

inline void	get_screen_size(void *mlx_ptr, int *size_x, int *size_y)
{
	(void)mlx_ptr;
//	mlx_get_screen_size(size_x, size_y);
	*size_x = 1920;
	*size_y = 1080;
}

#else

inline void	get_screen_size(void *mlx_ptr, int *size_x, int *size_y)
{
	mlx_get_screen_size(mlx_ptr, size_x, size_y);
}

#endif
