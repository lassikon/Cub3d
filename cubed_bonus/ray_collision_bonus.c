/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:45:04 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 11:07:32 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

float	ray_col_point(t_ray *ray, t_side side)
{
	if (side == HORIZONTAL)
	{
		if (ray->angle < PI)
		{
			ray->wall_side = NORTH;
			return ((int)(ray->x / TILE) * TILE + TILE - ray->x);
		}
		else
		{
			ray->wall_side = SOUTH;
			return (ray->x - (int)(ray->x / TILE) * TILE);
		}
	}
	if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
	{
		ray->wall_side = WEST;
		return (ray->y - (int)(ray->y / TILE) * TILE);
	}
	else
	{
		ray->wall_side = EAST;
		return ((int)(ray->y / TILE) * TILE + TILE - ray->y);
	}
}

static int	moving_door_state(t_game *game, t_ray *ray)
{
	if (ray->x < 0 || ray->x >= game->map_width
		|| ray->y < 0 || ray->y >= game->map_height)
		return (0);
	if (game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] >= 'a'
		&& game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] <= 'm')
		return (game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)]
			- 'a' + 1);
	else if (game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] >= 'n'
		&& game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] <= 'z')
		return (game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)]
			- 'n' + 1);
	return (0);
}

void	moving_door_collision(t_game *game, t_ray *ray, t_side side)
{
	if (side == HORIZONTAL)
	{
		ray->h_door_state = moving_door_state(game, ray);
		if (ray->h_door_state > 0)
			ray->door_h_dist = ray->distance_to_horizontal;
		if (ray->angle > PI)
			ray->door_h_col = ray->x - (int)(ray->x / TILE) * TILE;
		else
			ray->door_h_col = (int)(ray->x / TILE) * TILE + TILE - ray->x;
	}
	else if (side == VERTICAL)
	{
		ray->v_door_state = moving_door_state(game, ray);
		if (ray->v_door_state > 0)
			ray->door_v_dist = ray->distance_to_vertical;
		if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
			ray->door_v_col = ray->y - (int)(ray->y / TILE) * TILE;
		else
			ray->door_v_col = (int)(ray->y / TILE) * TILE + TILE - ray->y;
	}
}

int	closed_door_collision(t_game *game, t_ray *ray)
{
	if (ray->x < 0 || ray->x >= game->map_width
		|| ray->y < 0 || ray->y >= game->map_height)
		return (0);
	ray->door = 0;
	if (game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] == '2')
		return (1);
	return (0);
}

int	wall_collision(t_game *game, float ray_x, float ray_y)
{
	int	x;
	int	y;

	y = (int)ray_y;
	x = (int)ray_x;
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (game->map[y / TILE][x / TILE] == '1'
		|| game->map[y / TILE][x / TILE] == '2')
		return (1);
	return (0);
}
