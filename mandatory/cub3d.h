/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:54:53 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/16 10:13:39 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "token.h"
# include "../MLX42/include/glad/glad.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 576
# define IMG_HEIGHT 512
# define IMG_WIDTH 512
# define TILE 64
# define WALL_HEIGHT 64
# define PI 3.14159265359
# define FOV 1.0471975512
# define MOVE_SPEED 4
# define STRAFE_SPEED 2
# define ROTATION_SPEED 0.05235987755
# define COLL_OFFSET 16
# define MAX_DEPTH 64000
# define P_HEIGHT 32

# define MAP_CHARS "1 0NSEW"

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

typedef struct s_scene
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	mlx_texture_t *north_tex;
	mlx_texture_t *south_tex;
	mlx_texture_t *east_tex;
	mlx_texture_t *west_tex;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
	int		map_width;
	int		map_height;
	t_list	*tokens;
}			t_scene;

typedef enum e_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_side;

typedef struct ray_s
{
	float	x;
	float	y;
	float	col;
	t_side	wall_side;
	float	x_step;
	float	y_step;
	float	ty;
	int		tx;
	float	ty_step;
	float	tx_step;
	uint8_t	*pix;
	int		column;
	float	distance_to_horizontal;
	float	distance_to_vertical;
	int		height;
	int		wall_direction;
	float	distance;
	float	angle;
}	t_ray;

typedef struct s_render
{
	int	bottom_wall;
	int	top_wall;
	float brightness;
}		t_render;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t	*north_img;
	mlx_image_t	*south_img;
	mlx_image_t	*east_img;
	mlx_image_t	*west_img;
	int			*floor_color;
	int			*ceiling_color;
	t_player	p;
	t_render	render;
	char		**map;
	int			map_width;
	int			map_height;
	float		dist_to_proj_plane;
	float		vertical_center;
	int			frame_count;
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
	INVALID_PLAYER_ERR,
	MAP_BIG_ERR,
}	t_err_code;

typedef struct s_error_entry
{
	char		*message;
	t_err_code	code;
}	t_error_entry;

void	init_game(t_game *game, t_scene *scene);
void	init_textures(t_game *game, t_scene *scene);
void	move_player(t_game *game);
void	render_walls(t_game *game);
void	cast_ray(t_game *game, t_ray *ray);

/*parse and utils*/
int		gnl_chk(char **line, int fd);
void	tokenize(t_scene *scene, char *line);
void	parse(t_scene *scene, int argc, char **argv);
void	malloc_guard(t_scene *scene, char ***tmp, void *ptr);
size_t	ft_arrlen(char **arr);
char	*substr_guard(t_scene *scene, t_list **head);
void	write_map(t_scene *scene, t_list *head, int i);
void	extract_data(t_scene *scene);
void	is_valid(t_scene *scene);

/*frees and error*/
void	free_arr(char ***array);
void	free_lst(t_list **head);
void	free_scene(t_scene *scene);
void	error_handler(t_scene *scene, t_err_code code);
void	mlx_error_exit(t_game *game, t_scene *scene);

/*debug*/
void	print_array(char **array);
void	print_list(t_list *head);

#endif