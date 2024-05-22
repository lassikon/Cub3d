/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:54:53 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/22 14:51:39 by jberay           ###   ########.fr       */
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

# include "libft/include/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include "token.h"
# include "MLX42/include/glad/glad.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 576
# define TILE_SIZE 64
# define TILE 64
# define WALL_HEIGHT 64
# define PI 3.14159265359
# define FOV 1.0471975512 // 60 degrees
# define MOVE_SPEED 4
# define STRAFE_SPEED 2
# define ROTATION_SPEED (PI / 60) // 3 degrees
# define MINIMAP_SIZE 256
# define C_BUF 16
# define MAX_DEPTH 64000
# define P_HEIGHT 32
# define MOUSE_SENSITIVITY 500
# define LOOK_UP_AND_DOWN 1
# define DOOR_SPEED 1
# define ENEMY_SPEED 1.5


# define MAP_CHARS "1 023NSEW*" //1 = wall, 0 = empty space, 2 = closed door, 3 = open door, NSEW = player
# define C_CHARS "12abcdefghijklmnopqrstuvwxyz"

# define GREY2 0x808080FF
# define GREY 0x404040FF
# define RED 0xFF0000FF
# define BROWN 0x8B4513FF
# define DARK_BROWN 0x5A2B1DFF
# define OLIVE 0x808000FF
# define BLACK 0x000000FF
# define LIGHT_GREY 0xD3D3D3FF
# define WHITE 0xFFFFFFFF

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	int		height;
	int		jumping;
	int		jump_height[14];
}	t_player;

typedef struct s_enemy
{
	float	x;
	float	y;
	float	angle;
	int		height;
	bool	alive;
	mlx_texture_t	*tx[4];
	mlx_image_t		*img[4];
}	t_enemy;

typedef struct s_minimap
{
	float		x;
	float		y;
	float		map_x;
	float		map_y;
	int			color;
	mlx_image_t	*image;
}	t_minimap;

typedef struct s_scene
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*dr_texture;
	char			*fl_texture;
	char			*cl_texture;
	int				floor_color[3];
	int				ceiling_color[3];
	char			**map;
	int				map_width;
	int				map_height;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*east_tex;
	mlx_texture_t	*west_tex;
	mlx_texture_t	*door_tex;
	mlx_texture_t	*floor_tex;
	mlx_texture_t	*ceiling_tex;
	t_list			*tokens;
}					t_scene;

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
	float	tx;
	float	ty_step;
	float	tx_step;
	uint8_t	*pixel;
	int		column;
	float	distance_to_horizontal;
	float	distance_to_vertical;
	int		height;
	int		wall_direction;
	int		v_door_state;
	int		h_door_state;
	int		door;
	int		door_state;
	int		enemy_top;
	int		enemy_bottom;
	float	door_distance;
	float	door_h_dist;
	float	door_v_dist;
	float	door_h_col;
	float	door_v_col;
	float	door_col;
	float	distance;
	float	angle;
}			t_ray;

typedef struct s_render
{
	int		bottom_wall;
	int		top_wall;
	float	brightness;
	int		e_top;
	int		e_bottom;
	int		e_left;
	int		e_right;
}			t_render;

typedef struct s_math
{
	float		sin[SCREEN_WIDTH * 6];
	float		cos[SCREEN_WIDTH * 6];
	float		tan[SCREEN_WIDTH * 6];
	float		fishcos[360];
	float		ifishcos[360];
	float		isin[SCREEN_WIDTH * 6];
	float		icos[SCREEN_WIDTH * 6];
	float		itan[SCREEN_WIDTH * 6];
	float		trig_it;
	float		fish_it;
}				t_math;

typedef enum s_weapon_state
{
	IDLE,
	AIM,
	ANIMATING,
}	t_weapon_state;

typedef struct s_sprite
{
	mlx_texture_t	*hk53_fire_tx[14];
	mlx_image_t		*hk53_fire_img[14];
	mlx_texture_t	*hk53_aim_mid_tx[12];
	mlx_texture_t	*hk53_fire_mid_tx[13];
	mlx_image_t		*hk53_aim_mid_img[12];
	mlx_image_t		*hk53_fire_mid_img[13];
	int				weapon_aim;
	size_t			weapon_fire;
	t_weapon_state	weapon_state;
}					t_sprite;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_minimap		mini;
	mlx_image_t		*mini_img;
	mlx_image_t		*north_img;
	mlx_image_t		*south_img;
	mlx_image_t		*east_img;
	mlx_image_t		*west_img;
	mlx_image_t		*floor_img;
	mlx_image_t		*ceiling_img;
	mlx_image_t		*door_img;
	t_player		p;
	t_enemy			e[100];
	t_render		render;
	t_math			math;
	t_sprite		sprite;
	t_ray			rays[SCREEN_WIDTH];
	char			**map;
	int				*floor_color;
	int				*ceiling_color;
	int				map_width;
	int				map_height;
	float			dist_to_proj_plane;
	float			vertical_center;
	float			angle_step;
	double			frame_count;
	int				door_opening;
	int				door_closing;
	int				enemy_count;
	float	z_buffer[SCREEN_WIDTH];
}					t_game;

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

void	move_player(t_game *game);
void	move_enemy(t_game *game);
void	move_player_vertical(t_game *game);
void	move_mouse(t_game *game);
void	weapons(t_game *game);
void	render_walls(t_game *game);
void	minimap(t_game *game);
void	cast_ray(t_game *game, t_ray *ray);
int		get_rgba(int red, int green, int blue, int alpha);
void	operate_door(mlx_key_data_t data, void *param);
void	animate_door(t_game *game);
void	moving_door(t_game *game);
void	move_enemy(t_game *game);

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

/*debug*/
void	print_array(char **array);
void	print_list(t_list *head);


#endif