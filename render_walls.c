/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/02 16:29:01 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_column(t_game *game, t_ray ray, int column)
{
	int		height;
	int		y;
	int		color;

	height = TILE_SIZE / ray.distance * game->distance_to_projection_plane;
	if (height > SCREEN_HEIGHT)
		height = SCREEN_HEIGHT;
	y = SCREEN_HEIGHT / 2 - height / 2;
	// if (ray.wall_direction == 1)
	color = 0x00FF00FF; // Light green
	/* else if (ray.wall_direction == 2)
		color = 0x008000FF; // Dark green
	else if (ray.wall_direction == 3)
		color = 0x00FF0080; // Greenish blue
	else if (ray.wall_direction == 4)
		color = 0x008080FF; // Bluish green */
	while (y < SCREEN_HEIGHT / 2 + height / 2)
	{
		mlx_put_pixel(game->image, column, y, color);
		y++;
	}
}

int	ray_collision(int map[MAP_HEIGHT][MAP_WIDTH], int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH * TILE_SIZE || y < 0 || y >= MAP_HEIGHT * TILE_SIZE)
		return (1);
	if (map[y / TILE_SIZE][x / TILE_SIZE] == 1)
		return (1);
	return (0);
}

float	get_distance(int px, int py, int x, int y)
{
	if (x <= 0 || x >= MAP_WIDTH * TILE_SIZE || y <= 0 || y >= MAP_HEIGHT * TILE_SIZE)
		return (INT_MAX);
	return (sqrt((px - x) * (px - x) + (py - y) * (py - y)));
}

void	horizontal_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle > M_PI && ray->angle < 2 * M_PI)
		ray->hy = (game->p.y / TILE_SIZE) * TILE_SIZE - 1;
	else
		ray->hy = (game->p.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	ray->hx = game->p.x + (game->p.y - ray->hy) / tan(ray->angle);
	ray->hy_step = TILE_SIZE;
	if (ray->angle > M_PI && ray->angle < 2 * M_PI)
		ray->hy_step = -TILE_SIZE;
	ray->hx_step = TILE_SIZE / tan(ray->angle);
	ray->distance_to_horizontal = get_distance(game->p.x, game->p.y, ray->hx, ray->hy);
	while (ray_collision(game->map, ray->hx, ray->vy) == 0)
	{
		ray->hx += ray->hx_step;
		ray->hy += ray->hy_step;
		ray->distance_to_horizontal = get_distance(game->p.x, game->p.y, ray->hx, ray->hy);
	}
}

void	vertical_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
		ray->vx = (game->p.x / TILE_SIZE) * TILE_SIZE - 1;
	else
		ray->vx = (game->p.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	ray->vy = game->p.y + (game->p.x - ray->vx) * tan(ray->angle);
	ray->vx_step = TILE_SIZE;
	if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
		ray->vx_step = -TILE_SIZE;
	ray->vy_step = TILE_SIZE * tan(ray->angle);
	ray->distance_to_vertical = get_distance(game->p.x, game->p.y, ray->vx, ray->vy);
	while (ray_collision(game->map, ray->vx, ray->vy) == 0)
	{
		ray->vx += ray->vx_step;
		ray->vy += ray->vy_step;
		ray->distance_to_vertical = get_distance(game->p.x, game->p.y, ray->vx, ray->vy);
	}
}

void	cast_ray(t_game *game, t_ray *ray)
{
	horizontal_intersection(game, ray);
	vertical_intersection(game, ray);
	printf("Horizontal intersection: x = %d, y = %d, distance = %f\n", ray->hx, ray->hy, ray->distance_to_horizontal);
	printf("Vertical intersection: x = %d, y = %d, distance = %f\n", ray->vx, ray->vy, ray->distance_to_vertical);
	if (ray->distance_to_horizontal < ray->distance_to_vertical)
	{
		ray->distance = ray->distance_to_horizontal;
		ray->collision = 1;
	}
	else
	{
		ray->distance = ray->distance_to_vertical;
		ray->collision = 2;
	}
}

void	init_ray(t_ray *ray)
{
	ray->hx = 0;
	ray->hy = 0;
	ray->vx = 0;
	ray->vy = 0;
	ray->hx_step = 0;
	ray->hy_step = 0;
	ray->vx_step = 0;
	ray->vy_step = 0;
	ray->distance_to_horizontal = 0;
	ray->distance_to_vertical = 0;
	ray->collision = 0;
	ray->wall_direction = 0;
	ray->distance = 0;
}

void	render_walls(t_game *game)
{
	int		column;
	t_ray	ray;
	float	angle_step;

	column = 0;
	angle_step = FOV / SCREEN_WIDTH;
	ray.angle = game->p.angle - FOV / 2;
	// printf("Player position: x = %d, y = %d, angle = %f\n", game->p.x, game->p.y, game->p.angle);
	// printf("leftmost ray angle: %f\n", ray.angle);
	// printf("rightmost ray angle: %f\n", ray.angle + FOV);
	while (column < SCREEN_WIDTH)
	{
		if (ray.angle < 0)
			ray.angle += 2 * M_PI;
		else if (ray.angle > 2 * M_PI)
			ray.angle -= 2 * M_PI;
		ray.collision = 0;
		init_ray(&ray);
		cast_ray(game, &ray);
		draw_column(game, ray, column);
		column++;
		ray.angle += angle_step;
	}
}