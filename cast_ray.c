/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:06:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/15 13:53:08 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_collision(t_game *game, t_ray *ray)
{
	if (ray->x < 0 || ray->x >= game->map_width
		|| ray->y < 0 || ray->y >= game->map_height)
		return ;
	ray->door = 0;
	if (game->map[(int)(ray->y / TILE_SIZE)][(int)(ray->x / TILE_SIZE)] == 'D')
		ray->door = 1;
}

static int	wall_collision(t_game *game, float ray_x, float ray_y)
{
	int	x;
	int	y;

	y = (int)ray_y;
	x = (int)ray_x;
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (game->map[y / TILE_SIZE][x / TILE_SIZE] == 'D'
		|| game->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

static float	get_distance(t_game *game, float dx, float dy)
{
	if (dx < 0 || dx > game->map_width || (dy < 0 || dy > game->map_height))
		return (MAX_DEPTH);
	return (sqrt(((game->p.x - dx) * (game->p.x - dx))
			+ ((game->p.y - dy) * (game->p.y - dy))));
}

static void	horizontal_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == 0 || ray->angle == PI)
	{
		ray->distance_to_horizontal = MAX_DEPTH;
		return ;
	}
	else if (ray->angle > PI)
	{
		ray->y = (int)(game->p.y / TILE_SIZE) * TILE_SIZE - 0.001;
		ray->x = game->p.x + ((game->p.y - ray->y) * (-1 * game->math.itan[(int)(ray->angle * game->math.trig_it)]));
		ray->y_step = -TILE_SIZE;
		ray->x_step = TILE_SIZE / (-1 * game->math.tan[(int)(ray->angle * game->math.trig_it)]);
	}
	else
	{
		ray->y = (int)(game->p.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		ray->x = game->p.x + ((ray->y - game->p.y) * game->math.itan[(int)(ray->angle * game->math.trig_it)]);
		ray->y_step = TILE_SIZE;
		ray->x_step = TILE_SIZE * game->math.itan[(int)(ray->angle * game->math.trig_it)];
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

static void	vertical_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == PI / 2 || ray->angle == 3 * PI / 2)
	{
		ray->distance_to_vertical = MAX_DEPTH;
		return ;
	}
	else if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE_SIZE) * TILE_SIZE - 0.001;
		ray->y = game->p.y + ((game->p.x - ray->x) * (-1 * game->math.tan[(int)(ray->angle * game->math.trig_it)]));
		ray->x_step = -TILE_SIZE;
		ray->y_step = TILE_SIZE * (-1 * game->math.tan[(int)(ray->angle * game->math.trig_it)]);
	}
	else if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		ray->y = game->p.y + ((ray->x - game->p.x) * game->math.tan[(int)(ray->angle * game->math.trig_it)]);
		ray->x_step = TILE_SIZE;
		ray->y_step = TILE_SIZE * game->math.tan[(int)(ray->angle * game->math.trig_it)];
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
	door_collision(game, ray);
	vertical_intersection(game, ray);
	if (ray->distance_to_horizontal < ray->distance_to_vertical)
		ray->distance = ray->distance_to_horizontal;
	else
	{
		door_collision(game, ray);
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
