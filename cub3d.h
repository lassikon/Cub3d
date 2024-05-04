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
#define SCREEN_HEIGHT 512
#define TILE_SIZE 64
#define PI 3.14159265359
#define FOV 1.0471975512 // 60 degrees
#define MOVE_SPEED 4
#define STRAFE_SPEED 2
#define ROTATION_SPEED (PI / 90) // 2 degrees
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define MINIMAP_SIZE 128

# define MAP_CHARS " 01NSEW"

typedef struct  s_player {
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

typedef struct  ray_s {
	int		x;
	int		y;
	int		x_step;
	int		y_step;
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
	mlx_image_t	*minimap;
	t_player	p;
	char		**map;
	float		distance_to_projection_plane;
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
	INVALID_MAP_ERR,
	MAP_NOT_CLOSED_ERR,
}	t_err_code;

typedef enum e_free_func
{
	NFREE,
	FREE_SCENE,
	FREE_LST,
	FREE_ARR,
	FREE,
}	t_free_func;

typedef struct s_error_entry
{
	char		*message;
	t_err_code	code;
}	t_error_entry;

void	move_player(t_game *game);
void	render_walls(t_game *game);
int		wall_collision(char **map, int x, int y);

/*parse and utils*/
void	tokenize(t_list	**head, char *line);
void	parse(t_scene *scene, int argc, char **argv);
void	malloc_guard(t_scene *scene, t_list **head, char ***tmp, void *ptr);
size_t	ft_arrlen(char **arr);
char	*substr_guard(t_scene *scene, t_list **head);
void	write_map(t_scene *scene, t_list **head, \
	int i, size_t t_longest_row);
void	extract_data(t_scene *scene, t_list **head);
void	is_valid(t_scene *scene, size_t longest_row);

/*frees and error*/
void	free_arr(char ***array);
void	free_lst(t_list **head);
void	free_scene(t_scene *scene);
void	error_handler(void *data, t_free_func func, t_err_code code);

/*debug*/
void	print_array(char **array);

#endif