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

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define TILE_SIZE 64
#define FOV (M_PI / 3) // Field of view (60 degrees)
#define MOVEMENT_SPEED 4.0f
#define STRAFE_SPEED 2.5f
#define ROTATION_SPEED (M_PI / 100)
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

typedef struct  player_s{
	float	x;
	float	y;
	float	angle;
} player_t;

typedef struct  ray_s{
	float	x;
	float	y;
	float	distance;
	float	angle;
	int		hit;
	int 	vertical;
	int 	wall_direction;
} ray_t;

typedef struct s_game {
	mlx_t		*mlx;
	mlx_image_t	*image;
	player_t	p;
	int			map[MAP_HEIGHT][MAP_WIDTH];
} t_game;

void	move_player(t_game *game);
void	render_walls(t_game *game);

#endif