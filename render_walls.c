/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/21 10:23:17 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ceiling(t_game *game)
{
	int		x;
	int		y;
	int		color;
	float	b;

	y = 0;

	while (y <= game->vertical_center)
	{
		b = (game->vertical_center + 1) / (y + (float)game->vertical_center);
		if (b > 1)
			b = 1;
		if (b < 0)
			b = 0;
		x = 0;
		color = get_rgba(game->ceiling_color[0] * b, game->ceiling_color[1] * b, \
			game->ceiling_color[2] * b, 255);
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_floor(t_game *game)
{
	int		x;
	int		y;
	int		color;
	float	b;

	y = game->vertical_center;
	while (y < SCREEN_HEIGHT)
	{
		b = (y - game->vertical_center + 150) / SCREEN_HEIGHT;
		if (b > 1)
			b = 1;
		if (b < 0)
			b = 0;
		color = get_rgba(game->floor_color[0] * b, game->floor_color[1] * b, \
			game->floor_color[2] * b, 255);
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		y++;
	}
}

int	get_rgba(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

void	put_texture_pixel(t_game *game, t_ray *ray, mlx_image_t *img, int row)
{
	int	color;
	int	red;
	int	green;
	int	blue;
	int	alpha;

	ray->pixel = &img->pixels[(int)ray->ty * img->width * 4 + (int)ray->tx * 4];
	if (ray->pixel[3] != 0)
	{
		red = ray->pixel[0] * game->render.brightness;
		green = ray->pixel[1] * game->render.brightness;
		blue = ray->pixel[2] * game->render.brightness;
		alpha = ray->pixel[3];
		color = get_rgba(red, green, blue, alpha);
		mlx_put_pixel(game->image, ray->column, row, color);
	}
}

void	get_wall_ray_x_y(t_game *game, t_ray *ray)
{
	if (ray->wall_side == EAST || ray->wall_side == WEST)
		game->render.brightness = 180 / ray->distance;
	else
		game->render.brightness = 130 / ray->distance;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
}

static void	draw_wall(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int	row;

	row = 0;
	ray->ty = 0;
	ray->ty_step = (float)img->height / ray->height;
	if (game->render.top_wall < 0)
	{
		ray->ty += -game->render.top_wall * ray->ty_step;
		game->render.top_wall = 0;
		ray->height = SCREEN_HEIGHT;
	}
	get_wall_ray_x_y(game, ray);
	ray->tx = (float)(img->width / TILE_SIZE) * ray->col;
	ray->tx = fmod(ray->tx, img->width);
	ray->ty = fmod(ray->ty, img->height);
	while (row < ray->height)
	{
		if (game->render.top_wall + ray->height > SCREEN_HEIGHT)
			ray->height = SCREEN_HEIGHT - game->render.top_wall;
		put_texture_pixel(game, ray, img, game->render.top_wall + row);
		row++;
		ray->ty += ray->ty_step;
		if (ray->ty >= img->height)
			break ;
	}
}

void	get_floor_ray_x_y(t_game *game, t_ray *ray, int row)
{
	float	eye_to_floor;
	float	ratio;
	float	angle;
	int		fishtable;
	int		trigtable;

	if (row - game->vertical_center <= 0)
		return ;
	ratio = game->p.height / (row - game->vertical_center);
	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	trigtable = (int)(ray->angle * game->math.trig_it);
	angle = game->math.ifishcos[fishtable];
	eye_to_floor = ratio * game->dist_to_proj_plane * angle;
	ray->tx = game->p.x + game->math.cos[trigtable] * eye_to_floor;
	ray->ty = game->p.y + game->math.sin[trigtable] * eye_to_floor;
	game->render.brightness = 150 / eye_to_floor;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
}

/*draw floors*/
void	draw_floor(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int		row;

	if (!img)
		return ;
	row = (int)game->render.bottom_wall;
	while (row < SCREEN_HEIGHT)
	{
		get_floor_ray_x_y(game, ray, row);
		if (ray->tx < 0)
			ray->tx += TILE_SIZE;
		if (ray->ty < 0)
			ray->ty += TILE_SIZE;
		ray->tx = ray->tx - (int)(ray->tx / TILE_SIZE) * TILE_SIZE;
		ray->ty = ray->ty - (int)(ray->ty / TILE_SIZE) * TILE_SIZE;
		ray->tx = (float)img->width / TILE_SIZE * ray->tx;
		ray->ty = (float)img->height / TILE_SIZE * ray->ty;
		ray->tx = ((int)ray->tx % img->width);
		ray->ty = ((int)ray->ty % img->height);
		put_texture_pixel(game, ray, img, row);
		row++;
	}
}

void	get_ceiling_ray_x_y(t_game *game, t_ray *ray, int row)
{
	float	eye_to_floor;
	float	ratio;
	float	angle;
	int		fishtable;
	int		trigtable;

	if (game->vertical_center - row <= 0)
		return ;
	ratio = (WALL_HEIGHT - game->p.height) / (game->vertical_center - row);
	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	trigtable = (int)(ray->angle * game->math.trig_it);
	angle = game->math.ifishcos[fishtable];
	eye_to_floor = ratio * game->dist_to_proj_plane * angle;
	ray->tx = game->p.x + game->math.cos[trigtable] * eye_to_floor;
	ray->ty = game->p.y + game->math.sin[trigtable] * eye_to_floor;
	game->render.brightness = 100 / eye_to_floor;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
}

/*draw ceiling*/
void	draw_ceiling(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int		row;

	if (!img)
		return ;
	row = (int)game->render.top_wall;
	while (row >= 0)
	{
		get_ceiling_ray_x_y(game, ray, row);
		if (ray->tx < 0)
			ray->tx += TILE_SIZE; // Ensure positive texture coordinates
		if (ray->ty < 0)
			ray->ty += TILE_SIZE;
		ray->tx = ray->tx - (int)(ray->tx / TILE_SIZE) * TILE_SIZE;
		ray->ty = ray->ty - (int)(ray->ty / TILE_SIZE) * TILE_SIZE;
		ray->tx = (float)img->width / TILE_SIZE * ray->tx;
		ray->ty = (float)img->height / TILE_SIZE * ray->ty;
		ray->tx = ((int)ray->tx % img->width);
		ray->ty = ((int)ray->ty % img->height);
		put_texture_pixel(game, ray, img, row);
		row--;
	}
}

static void	render_column(t_game *game, t_ray *ray)
{
	mlx_image_t	*img;
	float		ratio;
	int			fishtable;

	img = NULL;
	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	ray->distance *= game->math.fishcos[fishtable];
	ratio = game->dist_to_proj_plane / ray->distance;
	game->render.bottom_wall = (ratio * game->p.height) + game->vertical_center;
	ray->height = (game->dist_to_proj_plane * WALL_HEIGHT) / ray->distance;
	game->render.top_wall = game->render.bottom_wall - (int)ray->height;
	if (ray->door == 1)
		img = game->door_img;
	else if (ray->wall_side == NORTH && ray->door == 0)
		img = game->north_img;
	else if (ray->wall_side == SOUTH && ray->door == 0)
		img = game->south_img;
	else if (ray->wall_side == EAST && ray->door == 0)
		img = game->east_img;
	else if (ray->wall_side == WEST && ray->door == 0)
		img = game->west_img;
	draw_wall(game, ray, img);
	draw_floor(game, ray, game->floor_img);
	draw_ceiling(game, ray, game->ceiling_img);
}

void	draw_moving_door(t_game *game, t_ray *ray)
{
	int	row;

	row = 0;
	ray->ty = 0;
	ray->ty_step = (float)game->door_img->height / ray->height;
	if (game->render.top_wall < 0)
	{
		ray->ty += -game->render.top_wall * ray->ty_step;
		game->render.top_wall = 0;
		ray->height = SCREEN_HEIGHT;
	}
	ray->tx = (float)(game->door_img->width / TILE_SIZE) * (ray->door_col + 5 * ray->door_state);
	if (ray->tx >= game->door_img->width)
		return ;
	game->render.brightness = 1;
	ray->tx = fmod(ray->tx, game->door_img->width);
	ray->ty = fmod(ray->ty, game->door_img->height);
	while (row < ray->height)
	{
		put_texture_pixel(game, ray, game->door_img, game->render.top_wall + row);
		row++;
		ray->ty += ray->ty_step;
		if (ray->ty >= game->door_img->height)
			break ;
	}
}

void	render_moving_door(t_game *game, t_ray *ray)
{
	float		ratio;
	int			fishtable;

	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	ray->door_distance *= game->math.fishcos[fishtable];
	ratio = game->dist_to_proj_plane / ray->door_distance;
	game->render.bottom_wall = (ratio * game->p.height) + game->vertical_center;
	ray->height = (game->dist_to_proj_plane * WALL_HEIGHT) / ray->door_distance;
	game->render.top_wall = game->render.bottom_wall - (int)ray->height;
	draw_moving_door(game, ray);
}

void	render_enemy(t_game *game, t_ray *ray)
{
	int		row;
	int		color;
	float	ratio;
	//int		fishtable;
	float	relative_x;
	float	relative_y;
	
	row = 0;
	relative_x = game->p.x - game->e.x;
	relative_y = game->p.y - game->e.y;
	ray->enemy_dist =  sqrt(relative_x * relative_x + relative_y * relative_y);
	// fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	// ray->enemy_dist *= game->math.ifishcos[fishtable];
	ratio = game->dist_to_proj_plane / ray->enemy_dist;
	game->render.bottom_wall = (ratio * game->p.height) + game->vertical_center;
	ray->height = (game->dist_to_proj_plane * WALL_HEIGHT) / ray->enemy_dist;
	game->render.top_wall = game->render.bottom_wall - (int)ray->height;
	ray->ty = 0;
	ray->ty_step = (float)game->e.img->height / ray->height;
	if (game->render.top_wall < 0)
	{
		ray->ty += -game->render.top_wall * ray->ty_step;
		ray->height += game->render.top_wall;
		game->render.top_wall = 0;
	}
	ray->tx = (float)(game->e.img->width / WALL_HEIGHT) * ray->enemy_col;
	ray->tx = fmod(ray->tx, game->e.img->width);
	ray->ty = fmod(ray->ty, game->e.img->height);
	while (row < ray->height)
	{
		color = get_rgba(255, 255, 0, 255);
		//mlx_put_pixel(game->image, ray->column, game->render.top_wall + row, color);
		put_texture_pixel(game, ray, game->e.img, game->render.top_wall + row);
		row++;
		ray->ty += ray->ty_step;
		if (ray->ty >= game->e.img->height)
			break ;
	}

	// int	row;

	// row = 0;
	// ray->ty = 0;
	// ray->ty_step = (float)img->height / ray->height;
	// if (game->render.top_wall < 0)
	// {
	// 	ray->ty += -game->render.top_wall * ray->ty_step;
	// 	game->render.top_wall = 0;
	// 	ray->height = SCREEN_HEIGHT;
	// }
	// get_wall_ray_x_y(game, ray);
	// ray->tx = (float)(img->width / TILE_SIZE) * ray->col;
	// ray->tx = fmod(ray->tx, img->width);
	// ray->ty = fmod(ray->ty, img->height);
	// while (row < ray->height)
	// {
	// 	if (game->render.top_wall + ray->height > SCREEN_HEIGHT)
	// 		ray->height = SCREEN_HEIGHT - game->render.top_wall;
	// 	put_texture_pixel(game, ray, img, game->render.top_wall + row);
	// 	row++;
	// 	ray->ty += ray->ty_step;
	// 	if (ray->ty >= img->height)
	// 		break ;
	// }
}
// void draw_sprite(t_game *game, int start_x, int end_x, int start_y, int end_y, int sprite_width, int sprite_height, float sprite_distance)
// {
//     for (int x = start_x; x < end_x; x++) {
//         if (x >= 0 && x < SCREEN_WIDTH && game->z_buffer[x] > sprite_distance) {
//             for (int y = start_y; y < end_y; y++) {
//                 if (y >= 0 && y < SCREEN_HEIGHT) {
//                     int texture_x = (x - start_x) * game->e.img->width / sprite_width;
//                     int texture_y = (y - start_y) * game->e.img->height / sprite_height;

//                     uint8_t *pixel = &game->e.img->pixels[(texture_y * game->e.img->width) + texture_x];
//                     uint8_t red = (*pixel >> 24) & 0xFF;
//                     uint8_t green = (*pixel >> 16) & 0xFF;
//                     uint8_t blue = (*pixel >> 8) & 0xFF;
//                     uint8_t alpha = (*pixel) & 0xFF;

//                     uint32_t color = (red << 24) | (green << 16) | (blue << 8) | alpha;
// 					color = get_rgba(255, 255, 0, 255);
//                     mlx_put_pixel(game->image, x, y, color);
//                 }
//             }
//         }
//     }
// }

// void	render_enemy(t_game *game)
// {
// 	float relative_x = game->e.x - game->p.x;
//     float relative_y = game->e.y - game->p.y;

// 	float sprite_distance =  sqrt(relative_x * relative_x + relative_y * relative_y);

// 	float camera_x = relative_x * cos(game->p.angle) + relative_y * sin(game->p.angle);
//     float camera_y = -relative_x * sin(game->p.angle) + relative_y * cos(game->p.angle);
// 	if (camera_y > 0)
// 	{
// 		// Calculate screen position and size
// 		int screen_x = (int)((camera_x / camera_y) * game->dist_to_proj_plane + (SCREEN_WIDTH / 2));
// 		int sprite_size = 64; // Example sprite size in world units
// 		int sprite_height = (int)((sprite_size / camera_y) * game->dist_to_proj_plane);
// 		int sprite_width = sprite_height;

// 		int start_x = screen_x - sprite_width / 2;
// 		int end_x = screen_x + sprite_width / 2;
// 		int start_y = (SCREEN_HEIGHT / 2) - sprite_height / 2;
// 		int end_y = (SCREEN_HEIGHT / 2) + sprite_height / 2;

// 		// Draw the sprite
// 		draw_sprite(game, start_x, end_x, start_y, end_y, sprite_width, sprite_height, sprite_distance);
//     }
// }

void	render_walls(t_game *game)
{
	t_ray	ray;
	float	angle_step;

	ray.column = 0;
	angle_step = FOV / SCREEN_WIDTH;
	ray.angle = game->p.angle - FOV / 2;
	if (!game->floor_img)
		render_floor(game);
	if (!game->ceiling_img)
		render_ceiling(game);
	while (ray.column < SCREEN_WIDTH)
	{
		if (ray.angle < 0)
			ray.angle += 2 * PI;
		else if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		cast_ray(game, &ray);
		if (ray.distance < MAX_DEPTH)
			render_column(game, &ray);
		if (ray.door_state && ray.door_distance < ray.distance)
			render_moving_door(game, &ray);
		if (ray.dist_h_e < MAX_DEPTH || ray.dist_v_e < MAX_DEPTH)
			render_enemy(game, &ray);
		ray.column++;
		ray.angle += angle_step;
	}
}
