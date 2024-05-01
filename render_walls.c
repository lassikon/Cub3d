/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/01 20:20:40 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_game *game, ray_t ray, int x)
{
	int		height;
	int		y;
	int		color;

	height = (int)(TILE_SIZE * SCREEN_HEIGHT / ray.distance);
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
		mlx_put_pixel(game->image, x, y, color);
		y++;
	}
}

void	cast_ray(t_game *game, ray_t *ray)
{
	float	x;
	float	y;

	x = game->p.x;
	y = game->p.y;
	ray->x = cos(ray->angle);
	ray->y = sin(ray->angle);
	while (1)
	{
		x += ray->x * 0.1f;
		y += ray->y * 0.1f;
		if (game->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == 1)
		{
			ray->distance = sqrt((game->p.x - x) * (game->p.x - x) + (game->p.y - y) * (game->p.y - y));
			ray->hit = 1;
			break ;
		}
	}
}

void	render_walls(t_game *game)
{
	int		x;
	ray_t	ray;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray.angle = game->p.angle - FOV / 2 + (float)x / (float)SCREEN_WIDTH * FOV;
		cast_ray(game, &ray);
		draw_wall(game, ray, x);
		x++;
	}
}