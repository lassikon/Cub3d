#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

# include "libft/include/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define TILE_SIZE 64
#define FOV (M_PI / 4) // Field of view (45 degrees)
#define RAY_COUNT SCREEN_WIDTH // Number of rays to cast

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 64
#define FOV (M_PI / 4) // Field of view (45 degrees)
#define MOVEMENT_SPEED 5.0f // Speed of player movement
#define ROTATION_SPEED (M_PI / 40) // Speed of player rotation

#endif