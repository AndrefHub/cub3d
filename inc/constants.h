#ifndef CONSTANTS_H
# define CONSTANTS_H


# define BAD_FILE -2
# define FRAMERATE 30
# define BAD_COLOUR (1 << 24)
# define BAD_COORD -1
# define PROJ_NAME "Cub3d"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1026
# define MAP_GRID_SIZE 32
# define TEXTURE_SIZE 32
# define MAX_RENDER_DISTANCE 5000
# define PI (float) M_PI
# define PL_ROT_KEY_SPEED 0.05f
# define PL_ROT_MOUSE_SPEED 0.002f
# define PL_SPEED 2.0f
# define PL_RADIUS 10.0f
# define PL_MAP_COLOR 0xFF0000
# define RAYS_COLOR 0xFFFF00
# define ABS_WALL_SIZE 840.0f
# define AIM_SIZE 4
# define AIM_COLOR 0xFF0000
# define MAX_TEXTURES 4
# define MAX_WALL_CHARS 4

# define WALL_CHARS "123456789@"

# ifdef __APPLE__
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
	E_KEY = 14,
};
# else
#  ifdef __linux__
enum e_keys
{
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	ESC_KEY = 113,
	UP_KEY = 83,
	LEFT_KEY = 91,
	DOWN_KEY = 81,
	RIGHT_KEY = 93,
	M_KEY = 109,
	E_KEY = 101,
};
#  endif
# endif


#endif
