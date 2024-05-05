/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/05 17:34:59 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_column(t_game *game, t_ray ray, int column)
{
	int		height;
	int		y;
	int		color;
	float	da;
	
	//fisheye
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
	color = 0x00FF00FF;
	while (y < SCREEN_HEIGHT / 2 + height / 2)
	{
		mlx_put_pixel(game->image, column, y, color);
		y++;
	}
}

int	wall_collision(char **map, int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH * TILE_SIZE || y < 0 || y >= MAP_HEIGHT * TILE_SIZE)
		return (1);
	if (map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

float	get_distance(int px, int py, int dx, int dy)
{
	if (dx < 0 || dx > (MAP_WIDTH * TILE_SIZE) || (dy < 0 || dy > (MAP_HEIGHT * TILE_SIZE)))
		return (INT_MAX);
	return (sqrt(((px - dx) * (px - dx)) + ((py - dy) * (py - dy))));
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
		if (game->p.y % TILE_SIZE == 0)
			ray->y = game->p.y - TILE_SIZE;
		else
			ray->y = (game->p.y / TILE_SIZE) * TILE_SIZE - 1;
		ray->x = game->p.x + ((game->p.y - ray->y) / (-1 * tanf(ray->angle)));
		ray->y_step = -TILE_SIZE;
		ray->x_step = TILE_SIZE / (-1 * tanf(ray->angle));
	}
	else
	{
		ray->y = (game->p.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		ray->x = game->p.x + ((ray->y - game->p.y) / tanf(ray->angle));
		ray->y_step = TILE_SIZE;
		ray->x_step = TILE_SIZE / (tanf(ray->angle));
	}
	ray->distance_to_horizontal = get_distance(game->p.x, game->p.y, ray->x, ray->y);
	if (ray->distance_to_horizontal == INT_MAX)
		return ;
	
	while (wall_collision(game->map, ray->x, ray->y) == 0)
	{
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_horizontal = get_distance(game->p.x, game->p.y, ray->x, ray->y);
		if (ray->distance_to_horizontal == INT_MAX)
			return ;
	}
}

void	vertical_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == PI / 2 || ray->angle ==  3 * PI / 2)
	{
		ray->distance_to_vertical = INT_MAX;
		return ;
	}
	else if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
	{
		if (game->p.x % TILE_SIZE == 0)
			ray->x = game->p.x - TILE_SIZE;
		else
			ray->x = (game->p.x / TILE_SIZE) * TILE_SIZE - 1;
		ray->y = game->p.y + ((game->p.x - ray->x) * (-1 * tanf(ray->angle)));
		ray->x_step = -TILE_SIZE;
		ray->y_step = TILE_SIZE * (-1 * tanf(ray->angle));
	}
	else if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
	{
		if (game->p.x % TILE_SIZE == 0)
			ray->x = game->p.x + TILE_SIZE;
		else
			ray->x = (game->p.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		ray->y = game->p.y + ((ray->x - game->p.x) * tanf(ray->angle));
		ray->x_step = TILE_SIZE;
		ray->y_step = TILE_SIZE * tanf(ray->angle);
	}
	ray->distance_to_vertical = get_distance(game->p.x, game->p.y, ray->x, ray->y);
	if (ray->distance_to_vertical == INT_MAX)
		return ;
	while (wall_collision(game->map, ray->x, ray->y) == 0)
	{
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_vertical = get_distance(game->p.x, game->p.y, ray->x, ray->y);
		if (ray->distance_to_vertical == INT_MAX)
			return ;
	}
}


void	cast_ray(t_game *game, t_ray *ray)
{
	horizontal_intersection(game, ray);
	vertical_intersection(game, ray);
	if (ray->distance_to_horizontal < ray->distance_to_vertical)
		ray->distance = ray->distance_to_horizontal;
	else
		ray->distance = ray->distance_to_vertical;
	printf("Horizontal distance: %f, Vertical distance: %f\n", ray->distance_to_horizontal, ray->distance_to_vertical);
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
	// printf("Player position: x = %f, y = %f, angle = %f\n", game->p.x, game->p.y, game->p.angle);
	while (column < SCREEN_WIDTH)
	{
		if (ray.angle < 0)
			ray.angle += 2 * PI;
		else if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		cast_ray(game, &ray);
		// printf("Player angle: %f, Ray angle: %f, distance: %f\n", game->p.angle, ray.angle, ray.distance);
		draw_column(game, ray, column);
		column++;
		ray.angle += angle_step;
	}
}
