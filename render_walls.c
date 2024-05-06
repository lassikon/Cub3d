/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/06 16:10:40 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_column(t_game *game, t_ray ray, int column)
{
	int		height;
	int		y;
	int		color;
	float	da;

	da = game->p.angle - ray.angle;
	if (da < 0)
		da += 2 * PI;
	if (da > 2 * PI)
		da -= 2 * PI;
	ray.distance *= cos(da);
	height = (int)(TILE_SIZE / ray.distance * game->distance_to_projection_plane);
	if (height > SCREEN_HEIGHT)
		height = SCREEN_HEIGHT;
	y = SCREEN_HEIGHT / 2 - height / 2;
	if (ray.distance_to_horizontal == ray.distance_to_vertical)
		color = 0x00FF0000; //red
	else if (ray.distance_to_horizontal < ray.distance_to_vertical)
		color = 0x0000FFFF;
	else
		color = 0x00FF00FF;
	while (y < SCREEN_HEIGHT / 2 + height / 2)
	{
		mlx_put_pixel(game->image, column, y, color);
		y++;
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
		return (INT_MAX);
	return (sqrt(((game->p.x - dx) * (game->p.x - dx)) + ((game->p.y - dy) * (game->p.y - dy))));
}

void	horizontal_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == 0 || ray->angle == PI)
	{
		ray->distance_to_horizontal = INT_MAX;
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
	if (ray->distance_to_horizontal == INT_MAX)
		return ;
	while (wall_collision(game, ray->x, ray->y) == 0)
	{
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_horizontal = get_distance(game, ray->x, ray->y);
		if (ray->distance_to_horizontal == INT_MAX)
			return ;
	}
}

void	vertical_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == PI / 2 || ray->angle == 3 * PI / 2)
	{
		ray->distance_to_vertical = INT_MAX;
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
	if (ray->distance_to_vertical == INT_MAX)
		return ;
	while (wall_collision(game, ray->x, ray->y) == 0)
	{
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_vertical = get_distance(game, ray->x, ray->y);
		if (ray->distance_to_vertical == INT_MAX)
			return ;
	}
}


void	cast_ray(t_game *game, t_ray *ray)
{
	horizontal_intersection(game, ray);
	vertical_intersection(game, ray);
	if (ray->distance_to_horizontal <= ray->distance_to_vertical)
		ray->distance = ray->distance_to_horizontal;
	else
		ray->distance = ray->distance_to_vertical;
}

void init_ray(t_ray *ray)
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

void init_ray(t_ray *ray)
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
