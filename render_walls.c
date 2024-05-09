/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/09 11:11:49 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_column(t_game *game, t_ray ray, int column)
{
	int		height;
	int		y;
	int		color = 0;
	float	da;

	da = game->p.angle - ray.angle;
	if (da < 0)
		da += 2 * PI;
	if (da > 2 * PI)
		da -= 2 * PI;
	ray.distance *= cos(da);
	if (ray.distance == MAX_DEPTH)
		return ;
	height = (int)(TILE_SIZE / ray.distance * game->distance_to_projection_plane);
	float ty_step = (float)game->no_img->height / height;
	float ty = 0;
	if (height > SCREEN_HEIGHT)
	{
		ty += (height - SCREEN_HEIGHT) / 2 * ty_step;
		height = SCREEN_HEIGHT;
	}
	y = game->vertical_center - height / 2;
	if (y < 0)
	{
		ty += -y * ty_step;
		y = 0;
	}
	float tx = (float)(game->no_img->width / TILE_SIZE) * ray.col;
	uint8_t *pixelstart;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	while (y < game->vertical_center + height / 2 && y < SCREEN_HEIGHT)
	{
		pixelstart = &game->no_img->pixels[(int)ty * game->no_img->width * 4 + (int)tx * 4];
		if (pixelstart[3] != 0)
		{
        	red = pixelstart[0];     // Red component
       		green = pixelstart[1];   // Green component
        	blue = pixelstart[2];    // Blue component
       		alpha = pixelstart[3];
        	color = get_rgba(red, green, blue, alpha);
			mlx_put_pixel(game->image, column, y, color);
		}
		y++;
		ty += ty_step;
		if (ty >= game->no_img->height)
			break ;
	}
}

int	wall_collision(t_game *game, float ray_x, float ray_y)
{
	int	x;
	int	y;

	y = (int)ray_y;
	x = (int)ray_x;
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (!game->map[y / TILE_SIZE][x / TILE_SIZE] || game->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

float	get_distance(t_game *game, float dx, float dy)
{
	if (dx < 0 || dx > game->map_width || (dy < 0 || dy > game->map_height))
		return (MAX_DEPTH);
	return (sqrt(((game->p.x - dx) * (game->p.x - dx)) + ((game->p.y - dy) * (game->p.y - dy))));
}

void	horizontal_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == 0 || ray->angle == PI)
	{
		ray->distance_to_horizontal = MAX_DEPTH;
		return ;
	}
	else if (ray->angle > PI)
	{
		ray->y = (int)(game->p.y / TILE_SIZE) * TILE_SIZE - 0.0001;
		ray->x = game->p.x + ((game->p.y - ray->y) / (-1 * tanf(ray->angle)));
		ray->y_step = -TILE_SIZE;
		ray->x_step = TILE_SIZE / (-1 * tanf(ray->angle));
	}
	else
	{
		ray->y = (int)(game->p.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		ray->x = game->p.x + ((ray->y - game->p.y) / tanf(ray->angle));
		ray->y_step = TILE_SIZE;
		ray->x_step = TILE_SIZE / (tanf(ray->angle));
	}
	ray->distance_to_horizontal = get_distance(game, ray->x, ray->y);
	if (ray->distance_to_horizontal == MAX_DEPTH)
		return ;
	while (wall_collision(game, ray->x, ray->y) == 0)
	{
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_horizontal = get_distance(game, ray->x, ray->y);
		if (ray->distance_to_horizontal == MAX_DEPTH)
			return ;
	}
}

void	vertical_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == PI / 2 || ray->angle == 3 * PI / 2)
	{
		ray->distance_to_vertical = MAX_DEPTH;
		return ;
	}
	else if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE_SIZE) * TILE_SIZE - 0.0001;
		ray->y = game->p.y + ((game->p.x - ray->x) * (-1 * tanf(ray->angle)));
		ray->x_step = -TILE_SIZE;
		ray->y_step = TILE_SIZE * (-1 * tanf(ray->angle));
	}
	else if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		ray->y = game->p.y + ((ray->x - game->p.x) * tanf(ray->angle));
		ray->x_step = TILE_SIZE;
		ray->y_step = TILE_SIZE * tanf(ray->angle);
	}
	ray->distance_to_vertical = get_distance(game, ray->x, ray->y);
	if (ray->distance_to_vertical == MAX_DEPTH)
		return ;
	while (wall_collision(game, ray->x, ray->y) == 0)
	{
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_vertical = get_distance(game, ray->x, ray->y);
		if (ray->distance_to_vertical == MAX_DEPTH)
			return ;
	}
}


void	cast_ray(t_game *game, t_ray *ray)
{
	horizontal_intersection(game, ray);
	if (ray->angle < PI)
	{
		ray->wall_side = NORTH;
		ray->col = (int)(ray->x / TILE_SIZE) * TILE_SIZE + TILE_SIZE - ray->x;
	}
	else
	{
		ray->wall_side = SOUTH;
		ray->col = ray->x - (int)(ray->x / TILE_SIZE) * TILE_SIZE;
	}
	vertical_intersection(game, ray);
	if (ray->distance_to_horizontal <= ray->distance_to_vertical)
		ray->distance = ray->distance_to_horizontal;
	else
	{
		ray->distance = ray->distance_to_vertical;
		ray->col = ray->y;
		if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
		{
			ray->wall_side = WEST;
			ray->col = ray->y - (int)(ray->y / TILE_SIZE) * TILE_SIZE;
		}
		else
		{
			ray->wall_side = EAST;
			ray->col = (int)(ray->y / TILE_SIZE) * TILE_SIZE + TILE_SIZE - ray->y;
		}
	}
}

void	init_ray(t_ray *ray)
{
	ray->x = 0;
	ray->y = 0;
	ray->x_step = 0;
	ray->y_step = 0;
	ray->distance_to_horizontal = 0;
	ray->distance_to_vertical = 0;
	ray->collision = 0;
	ray->wall_direction = 0;
	ray->distance = 0;
	ray->angle = 0;
}

void	render_walls(t_game *game)
{
	int		column;
	t_ray	ray;
	float	angle_step;

	init_ray(&ray);
	column = 0;
	angle_step = FOV / SCREEN_WIDTH;
	ray.angle = game->p.angle - FOV / 2;
	while (column < SCREEN_WIDTH)
	{
		if (ray.angle < 0)
			ray.angle += 2 * PI;
		else if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		cast_ray(game, &ray);
		draw_column(game, ray, column);
		column++;
		ray.angle += angle_step;
	}
}
