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
# include "token.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define TILE_SIZE 64
#define FOV (M_PI / 3) // Field of view (60 degrees)
#define MOVEMENT_SPEED 4.0f
#define STRAFE_SPEED 2.5f
#define ROTATION_SPEED (M_PI / 100)
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

typedef struct  s_player{
	int		x;
	int		y;
	float	angle;
} t_player;

typedef struct s_scene
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
}			t_scene;

typedef struct  ray_s{
	int		hx;
	int		hy;
	int		vx;
	int		vy;
	int		hx_step;
	int		hy_step;
	int		vx_step;
	int		vy_step;
	float	distance_to_horizontal;
	float	distance_to_vertical;
	int		collision;
	int 	wall_direction;
	float	distance;
	float	angle;
} t_ray;

typedef struct s_game {
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_player	p;
	int			map[MAP_HEIGHT][MAP_WIDTH];
	int			distance_to_projection_plane;
} t_game;

void	move_player(t_game *game);
void	render_walls(t_game *game);
void	check_args(t_scene *scene, int argc, char **argv);
void    tokenize(t_list	**head, char *line);
void	malloc_guard(t_list **head, void *ptr);

#endif