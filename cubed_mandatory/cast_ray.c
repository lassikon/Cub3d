/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:06:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/21 14:10:57 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	wall_collision(t_game *game, float ray_x, float ray_y)
{
	int	x;
	int	y;

	y = (int)ray_y;
	x = (int)ray_x;
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (game->map[y / TILE][x / TILE] == '1')
		return (1);
	return (0);
}

static float	get_distance(t_game *game, float dx, float dy)
{
	if (dx < 0 || (int)dx >= game->map_width
		|| dy < 0 || (int)dy >= game->map_height)
		return (MAX_DEPTH);
	return (sqrt(((game->p.x - dx) * (game->p.x - dx))
			+ ((game->p.y - dy) * (game->p.y - dy))));
}

static void	horizontal_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == 0 || ray->angle == PI)
		ray->distance_to_horizontal = MAX_DEPTH;
	else if (ray->angle > PI)
	{
		ray->y = (int)(game->p.y / TILE) * TILE - 0.001;
		ray->x = game->p.x + ((game->p.y - ray->y) / (-1 * tanf(ray->angle)));
		ray->y_step = -TILE;
		ray->x_step = TILE / (-1 * tanf(ray->angle));
	}
	else
	{
		ray->y = (int)(game->p.y / TILE) * TILE + TILE;
		ray->x = game->p.x + ((ray->y - game->p.y) / tanf(ray->angle));
		ray->y_step = TILE;
		ray->x_step = TILE / (tanf(ray->angle));
	}
	ray->distance_to_horizontal = get_distance(game, ray->x, ray->y);
	while (wall_collision(game, ray->x, ray->y) == 0)
	{
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_horizontal = get_distance(game, ray->x, ray->y);
		if (ray->distance_to_horizontal == MAX_DEPTH)
			return ;
	}
}

static void	vertical_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == PI / 2 || ray->angle == 3 * PI / 2)
		ray->distance_to_vertical = MAX_DEPTH;
	else if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE) * TILE - 0.001;
		ray->y = game->p.y + ((game->p.x - ray->x) * (-1 * tanf(ray->angle)));
		ray->x_step = -TILE;
		ray->y_step = TILE * (-1 * tanf(ray->angle));
	}
	else if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE) * TILE + TILE;
		ray->y = game->p.y + ((ray->x - game->p.x) * tanf(ray->angle));
		ray->x_step = TILE;
		ray->y_step = TILE * tanf(ray->angle);
	}
	ray->distance_to_vertical = get_distance(game, ray->x, ray->y);
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
	ray->wall_side = NORTH;
	ray->col = (int)(ray->x / TILE) * TILE + TILE - ray->x;
	if (ray->angle > PI)
	{
		ray->wall_side = SOUTH;
		ray->col = ray->x - (int)(ray->x / TILE) * TILE;
	}
	ray->distance = ray->distance_to_horizontal;
	vertical_intersection(game, ray);
	if (ray->distance_to_vertical > ray->distance_to_horizontal)
		return ;
	ray->distance = ray->distance_to_vertical;
	ray->wall_side = WEST;
	ray->col = ray->y - (int)(ray->y / TILE) * TILE;
	if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
	{
		ray->wall_side = EAST;
		ray->col = (int)(ray->y / TILE) * TILE + TILE - ray->y;
	}
}
