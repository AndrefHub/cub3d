#ifndef CONSTANTS_H
# define CONSTANTS_H

# define BAD_FILE -2
# define FRAMERATE 30
# define CLOCKS_PER_FRAME 1000 / FRAMERATE
# define BAD_COLOUR (1 << 24)
# define BAD_COORD -1
# define PROJ_NAME "Cub3d"
//# define WIN_WIDTH 2560
//# define WIN_HEIGHT 1440
 # define WIN_WIDTH 1280
 # define WIN_HEIGHT 720
//# define WIN_WIDTH 1920
//# define WIN_HEIGHT 1026
# define TEXTURE_SIZE 192
# define MAX_RENDER_DISTANCE 5000
# define PI (float) M_PI
# define PL_ROT_KEY_SPEED 0.05f
# define PL_ROT_MOUSE_SPEED 0.002f
# define PL_SPEED 2.0f
# define PL_ACCELERATION 2.5f
# define PL_RADIUS 0.2f
# define PL_MAP_COLOR 0xFF0000
# define EN_SPEED 0.03f
# define RAYS_COLOR 0xFFDD2D
# define ABS_WALL_SIZE 992.0f
//# define ABS_WALL_SIZE 2000.0f
# define PERSPECTIVE 4.72f
# define AIM_SIZE 4
# define AIM_COLOR 0xFF0000
# define MAX_ENEMIES 1
// # define MAX_WALL_CHARS 4
# define MAX_WALL_CHARS 10
# define MAX_SOUNDS 2
# define MAX_FONT_CHARS 224
# define ENEMY_RELOAD 1000
# define PL_INVINCIBILITY 2000
# define FONT_SIZE 240
# define FONT_OFFSET 32

// # define WALL_CHARS "1D23456789"
# define WALL_CHARS "123456789D"
# define CARDINAL_POINTS "NSWE"
# define BONUS "BONUS"
# define USE_PATH_PREFIX "USE_PATH_PREFIX"

# ifndef ASSETS_PATH
//#  define ASSETS_PATH "."
# define ASSETS_PATH "/Users/lsherry/goinfre"
# endif

# define WALL_PREFIX "W"
# define ENTITY_PREFIX "E"
# define SOUND_PREFIX "S"
# define FONT_PREFIX "F"

# ifdef __APPLE__
# define CHAR_OFFSET 0
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
	LEFT_CTRL_KEY = 256, //59
	BACKSPACE = 51,
	ENTER = 36,
};
# else
# define CHAR_OFFSET 256
#  ifdef __linux__
enum e_keys
{
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	ESC_KEY = 65307,
	UP_KEY = 65362,
	LEFT_KEY = 65361,
	DOWN_KEY = 65364,
	RIGHT_KEY = 65363,
	M_KEY = 109,
	E_KEY = 101,
	LEFT_CTRL_KEY = 65507,
	BACKSPACE = 65288,
	ENTER = 65293,
};
#  endif
# endif
enum layout
{
	VTop = 001,
	VCenter = 002,
	VBottom = 004,
	HLeft = 010,
	HCenter = 020,
	HRight = 040
};

#endif