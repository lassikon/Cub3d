/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:54:53 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 12:44:11 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# include "token_bonus.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 576
# define TILE_SIZE 64
# define TILE 64
# define WALL_HEIGHT 64
# define PI 3.14159265359
# define FOV 1.0471975512
# define MOVE_SPEED 4
# define STRAFE_SPEED 2
# define ROTATION_SPEED 0.05235987755
# define MINIMAP_SIZE 256
# define C_BUF 16
# define E_SIZE 48
# define MAX_DEPTH 64000
# define P_HEIGHT 32
# define E_HEIGHT 48
# define MOUSE_SENSITIVITY 500
# define DOOR_SPEED 1
# define ENEMY_SPEED 2.5

# define MAP_CHARS "1 023NSEW*"
# define C_CHARS "12abcdefghijklmnopqrstuvwxyz"

# define GREY 0x404040FF
# define RED 0xFF0000FF
# define DARK_BROWN 0x5A2B1DFF
# define OLIVE 0x808000FF
# define BLACK 0x000000FF
# define LIGHT_GREY 0xA0A0A0FF

# define MSG_MALLOC "Error\nMalloc failed\n"
# define MSG_ARG "Error\nInvalid arguments\n"
# define MSG_FILE_EXT "Error\nInvalid file extension\n"
# define MSG_FILE_OPEN "Error\nFailed to open file\n"
# define MSG_SCENE_FORMAT "Error\nInvalid scene format\n"
# define MSG_INVALID_MAP "Error\nFound invalid map characters\n"
# define MSG_MAP_NOT_CLOSED "Error\nMap is not closed\n"
# define MSG_INVALID_PLAYER "Error\nInvalid player\n"
# define MSG_MAP_BIG "Error\nMap too big\n"
# define MSG_ENEMIES "Error\nToo many enemies\n"

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	int		height;
	int		jumping;
	int		jump_height[14];
	int		hp;
	int		regen_cooldown;
}	t_player;

typedef struct s_enemy
{
	float			x;
	float			y;
	float			angle;
	float			distance;
	int				height;
	int				dying;
	int				attacking;
	bool			alive;
	bool			rendered;
	mlx_image_t		*img[4];
	mlx_image_t		*aimg[3];
	mlx_image_t		*dimg[9];
}	t_enemy;

typedef struct s_minimap
{
	float		x;
	float		y;
	float		map_x;
	float		map_y;
	int			dist;
	int			radius;
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
	mlx_texture_t	*e_tex[4];
	mlx_texture_t	*ea_tex[3];
	mlx_texture_t	*ed_tex[9];
	mlx_texture_t	*hp_txs[10];
	mlx_texture_t	*hk53_aim_mid_tx[12];
	mlx_texture_t	*hk53_fire_mid_tx[13];
	mlx_texture_t	*hk53_fire_tx[14];
	mlx_texture_t	*game_over_tex;
	mlx_texture_t	*win_tex;
	t_list			*tokens;
}					t_scene;

typedef enum e_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	HORIZONTAL,
	VERTICAL,
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
	int		sprite_screen_x;
	float	distance_to_horizontal;
	float	distance_to_vertical;
	int		height;
	int		wall_direction;
	int		v_door_state;
	int		h_door_state;
	int		door;
	int		door_state;
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
	AIM_ANIMATING,
}	t_weapon_state;

typedef struct s_sprite
{
	mlx_image_t		*hk53_fire_img[14];
	mlx_image_t		*hk53_aim_mid_img[12];
	mlx_image_t		*hk53_fire_mid_img[13];
	int				aim_frme;
	size_t			fire_frme;
	t_weapon_state	state;
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
	mlx_image_t		*hp_imgs[10];
	mlx_image_t		*game_over_img;
	mlx_image_t		*win_img;
	t_player		p;
	t_enemy			e[100];
	t_render		render;
	t_math			math;
	t_sprite		gun;
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
	int				enemy_count;
	int				in_crosshairs_id;
	int				next_enemy_to_render;
	bool			over;
	bool			victory;
	bool			keep_playing;
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
	ENEMIES_ERR,
}	t_err_code;

typedef struct s_error_entry
{
	char		*message;
	t_err_code	code;
}	t_error_entry;

/*init game*/
void	init_textures(t_game *game, t_scene *scene);
void	load_textures(t_game *game, t_scene *scene);
void	get_texture_name(char *buffer, char *path, int i);
void	load_weapon_textures(t_game *game, t_scene *scene);
void	init_game(t_game *game, t_scene *scene);
void	init_math_tables(t_game *game);
void	init_jump_height_table(t_game *game);
void	enemy_textures(t_game *game, t_scene *scene);
void	get_texture_name(char *buffer, char *path, int i);

/*movement*/
void	move_player(t_game *game);
void	move_player_vertical(t_game *game);
void	move_mouse(t_game *game);
void	move_enemies(t_game *game);
int		move_collision(t_game *game, int x, int y);
void	enemy_attack(t_game *game, int id);

/*minimap*/
void	minimap(t_game *game);

/*game state*/
void	game_over(t_game *game);
int		all_enemies_dead(t_game *game);
void	hitpoints(t_game *game, double frame);

/*weapons*/
void	weapons(t_game *game);
void	disable_img_frames(mlx_image_t **img, int frames);

/*doors*/
void	operate_door(mlx_key_data_t data, void *param);
void	update_door_state(t_game *game);
void	moving_door(t_game *game);

/*raycasting*/
void	cast_ray(t_game *game, t_ray *ray);
void	moving_door_collision(t_game *game, t_ray *ray, t_side side);
int		closed_door_collision(t_game *game, t_ray *ray);
int		wall_collision(t_game *game, float ray_x, float ray_y);
float	get_distance(t_game *game, float dx, float dy);
float	ray_col_point(t_ray *ray, t_side side);
void	init_ray(t_ray *ray);

/*rendering*/
void	put_texture_pixel(t_game *game, t_ray *ray, mlx_image_t *img, int row);
void	get_brightness_lvl(t_game *game, t_ray *ray);
int		get_rgba(int red, int green, int blue, int alpha);
void	render_enemies(t_game *game);
void	render_walls(t_game *game);
void	render_floor_color(t_game *game);
void	draw_floor(t_game *game, t_ray *ray, mlx_image_t *img);
void	render_ceiling_color(t_game *game);
void	draw_ceiling(t_game *game, t_ray *ray, mlx_image_t *img);
void	get_enemy_tx_ty(t_game *game, t_ray *eray, float ratio, int i);
void	get_enemy_x_y(t_game *game, t_ray *eray, int i);

/*parse and utils*/
void	init_scene(t_scene *scene);
int		gnl_chk(char **line, int fd);
void	tokenize(t_scene *scene, char *line);
void	parse(t_scene *scene, int argc, char **argv);
void	malloc_guard(t_scene *scene, char ***tmp, void *ptr);
size_t	ft_arrlen(char **arr);
char	*substr_guard(t_scene *scene, t_list **head);
void	extract_data(t_scene *scene);
void	is_valid(t_scene *scene);
void	ft_itoa_stack(char *buf, int n);
int		is_arrdigit(char **arr);

/*frees and error*/
void	free_arr(char ***array);
void	free_lst(t_list **head);
void	free_scene(t_scene *scene);
void	error_handler(t_scene *scene, t_err_code code);
void	mlx_error_exit(t_game *game, t_scene *scene);
void	delete_textures(t_scene *scene);

#endif