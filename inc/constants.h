#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PROJ_NAME "Cub3d"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1026
# define MAP_GRID_SIZE 32
# define MAX_RENDER_DISTANCE 1000
# define RAYS 512
# define PI (float) M_PI
# define PL_ROT_KEY_SPEED 0.05f
# define PL_ROT_MOUSE_SPEED 0.002f
# define PL_SPEED 2.0f
# define PL_MAP_COLOR 0xFF0000
# define RAYS_COLOR 0xFFFF00
# define ABS_WALL_SIZE 840.0f
# define AIM_SIZE 4
# define AIM_COLOR 0xFF0000


enum e_keys
{
	W_KEY = 13,
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	ESC_KEY = 53,
	UP_KEY = 126,
	LEFT_KEY = 123,
	DOWN_KEY = 125,
	RIGHT_KEY = 124,
	M_KEY = 46,
};



#endif
