#ifndef __DEFINES_H
# define __DEFINES_H

# define WINDOW_W 800
# define WINDOW_H 350
# define MAX_SOURCE_SIZE 0x100000
# define TEXTURES_COUNT 8
# define G1 0.01745329
# define G90 1.5707963f
# define G180 3.1415926f
# define G360 6.2831852f
# define MOVING_SPEED_PER_HALF_SEC 1000.0
# define ROTATION_SPEED_PER_HALF_SEC 80.0
# define MOUSE_SENSIVITY 0.002
# define MOUSE_UP_DOWN_SENSIVITY 1
# define PLAYER_HEIGHT 400
# define PLAYER_HEAD_SIZE 200
# define MAX_CLIMB_HEIGHT 300
# define JUMP_HEIGHT 1000
# define PL_COL_SZ 10
# define MENU_COLOR 0x00FF00
# define MAX_FPS 500

#endif
#ifdef __APPLE__
	# define CLKS_P_S (CLOCKS_PER_SEC * 2)
#else
	# define CLKS_P_S CLOCKS_PER_SEC
#endif