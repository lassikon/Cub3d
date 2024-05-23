/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:06:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/23 13:10:45 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initial_horizontal_step(t_game *game, t_ray *ray)
{
	if (ray->angle > PI)
	{
		ray->y = (int)(game->p.y / TILE) * TILE - 0.001;
		ray->x = game->p.x + ((game->p.y - ray->y)
				* (-1 * game->math.itan[(int)(ray->angle
						* game->math.trig_it)]));
		ray->y_step = -TILE;
		ray->x_step = TILE * (-1 * game->math.itan[(int)(ray->angle
					* game->math.trig_it)]);
	}
	else
	{
		ray->y = (int)(game->p.y / TILE) * TILE + TILE;
		ray->x = game->p.x + ((ray->y - game->p.y)
				* game->math.itan[(int)(ray->angle * game->math.trig_it)]);
		ray->y_step = TILE;
		ray->x_step = TILE * game->math.itan[(int)(ray->angle
				* game->math.trig_it)];
	}
}

static void	horizontal_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == 0 || ray->angle == PI)
	{
		ray->distance_to_horizontal = MAX_DEPTH;
		return ;
	}
	initial_horizontal_step(game, ray);
	ray->distance_to_horizontal = get_distance(game, ray->x, ray->y);
	while (wall_collision(game, ray->x, ray->y) == 0)
	{
		if (ray->h_door_state == 0)
			moving_door_collision(game, ray, HORIZONTAL);
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_horizontal = get_distance(game, ray->x, ray->y);
		if (ray->distance_to_horizontal == MAX_DEPTH)
			return ;
	}
}

static void	initial_vertical_step(t_game *game, t_ray *ray)
{
	if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE) * TILE - 0.001;
		ray->y = game->p.y + ((game->p.x - ray->x)
				* (-1 * game->math.tan[(int)(ray->angle
						* game->math.trig_it)]));
		ray->x_step = -TILE;
		ray->y_step = TILE * (-1 * game->math.tan[(int)(ray->angle
					* game->math.trig_it)]);
	}
	else if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE) * TILE + TILE;
		ray->y = game->p.y + ((ray->x - game->p.x)
				* game->math.tan[(int)(ray->angle * game->math.trig_it)]);
		ray->x_step = TILE;
		ray->y_step = TILE * game->math.tan[(int)(ray->angle
				* game->math.trig_it)];
	}
}

static void	vertical_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle == PI / 2 || ray->angle == 3 * PI / 2)
	{
		ray->distance_to_vertical = MAX_DEPTH;
		return ;
	}
	initial_vertical_step(game, ray);
	ray->distance_to_vertical = get_distance(game, ray->x, ray->y);
	while (wall_collision(game, ray->x, ray->y) == 0)
	{
		if (ray->v_door_state == 0)
			moving_door_collision(game, ray, VERTICAL);
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_vertical = get_distance(game, ray->x, ray->y);
		if (ray->distance_to_vertical == MAX_DEPTH)
			return ;
	}
}

void	cast_ray(t_game *game, t_ray *ray)
{
	init_ray(ray);
	horizontal_intersection(game, ray);
	ray->col = ray_col_point(ray, HORIZONTAL);
	if (closed_door_collision(game, ray))
		ray->door = 1;
	ray->distance = ray->distance_to_horizontal;
	vertical_intersection(game, ray);
	if (ray->h_door_state > 0 && ray->door_h_dist < ray->door_v_dist)
	{
		ray->door_distance = ray->door_h_dist;
		ray->door_state = ray->h_door_state;
		ray->door_col = ray->door_h_col;
	}
	if (ray->v_door_state > 0 && ray->door_v_dist < ray->door_h_dist)
	{
		ray->door_distance = ray->door_v_dist;
		ray->door_state = ray->v_door_state;
		ray->door_col = ray->door_v_col;
	}
	if (ray->distance_to_vertical > ray->distance_to_horizontal)
		return ;
	ray->distance = ray->distance_to_vertical;
	ray->col = ray_col_point(ray, VERTICAL);
	if (closed_door_collision(game, ray))
		ray->door = 1;
}

