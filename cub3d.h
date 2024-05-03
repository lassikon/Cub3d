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

typedef struct player_s
{
	float	x;
	float	y;
	float	angle;
} 			player_t;

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

/*error*/
typedef enum e_err_code
{
	NO_ERR,
	MALLOC_ERR,
	ARG_ERR,
	FILE_EXT_ERR,
	FILE_OPEN_ERR,
	SCENE_FORMAT_ERR,
	MAP_NOT_CLOSED_ERR,
}	t_err_code;

typedef struct s_error_entry
{
	char		*message;
	t_err_code	code;
}	t_error_entry;

void	move_player(t_game *game);
void	render_walls(t_game *game);

void	check_args(t_scene *scene, int argc, char **argv);
void	tokenize(t_list	**head, char *line);
void	write_data(t_scene *scene, t_list **head);
void	is_valid(t_scene *scene, size_t longest_row);
void	malloc_guard_lst(t_list **head, void *ptr);
void	malloc_guard_scene(t_scene *scene, t_list **head, char ***tmp, void *ptr);
size_t	ft_arrlen(char **arr);
void	free_arr(char ***array);
void	free_lst(t_list **head);
void	free_scene(t_scene *scene);
void	error_handler(t_scene *scene, t_err_code code);

/*debug*/
void	print_array(char **array);

#endif