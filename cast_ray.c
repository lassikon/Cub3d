/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:06:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/22 11:38:38 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	moving_door_collision(t_game *game, t_ray *ray)
{
	if (ray->x < 0 || ray->x >= game->map_width
		|| ray->y < 0 || ray->y >= game->map_height)
		return (0);
	if (game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] >= 'a'
		&& game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] <= 'm')
		return (game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] - 'a' + 1);
	else if (game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] >= 'n'
		&& game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] <= 'z')
		return (game->map[(int)(ray->y / TILE)][(int)(ray->x / TILE)] - 'n' + 1);
	return (0);
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

static int	wall_collision(t_game *game, float ray_x, float ray_y)
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

static float	get_distance(t_game *game, float dx, float dy)
{
	if (dx < 0 || dx > game->map_width || (dy < 0 || dy > game->map_height))
		return (MAX_DEPTH);
	return (sqrt(((game->p.x - dx) * (game->p.x - dx))
			+ ((game->p.y - dy) * (game->p.y - dy))));
}

static void	horizontal_intersection(t_game *game, t_ray *ray)
{
	ray->h_door_state = 0;
	ray->door_h_dist = MAX_DEPTH;
	if (ray->angle == 0 || ray->angle == PI)
	{
		ray->distance_to_horizontal = MAX_DEPTH;
		return ;
	}
	else if (ray->angle > PI)
	{
		ray->y = (int)(game->p.y / TILE) * TILE - 0.001;
		ray->x = game->p.x + ((game->p.y - ray->y) * (-1 * game->math.itan[(int)(ray->angle * game->math.trig_it)]));
		ray->y_step = -TILE;
		ray->x_step = TILE * (-1 * game->math.itan[(int)(ray->angle * game->math.trig_it)]);
	}
	else
	{
		ray->y = (int)(game->p.y / TILE) * TILE + TILE;
		ray->x = game->p.x + ((ray->y - game->p.y) * game->math.itan[(int)(ray->angle * game->math.trig_it)]);
		ray->y_step = TILE;
		ray->x_step = TILE * game->math.itan[(int)(ray->angle * game->math.trig_it)];
	}
	ray->distance_to_horizontal = get_distance(game, ray->x, ray->y);
	if (game->door_opening || game->door_closing)
	{
		ray->h_door_state = moving_door_collision(game, ray);
		if (ray->h_door_state > 0)
			ray->door_h_dist = ray->distance_to_horizontal;
		if (ray->angle > PI)
			ray->door_h_col = ray->x - (int)(ray->x / TILE) * TILE;
		else
			ray->door_h_col = (int)(ray->x / TILE) * TILE + TILE - ray->x;
	}
	if (ray->distance_to_horizontal == MAX_DEPTH)
		return ;
	while (wall_collision(game, ray->x, ray->y) == 0)
	{
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_horizontal = get_distance(game, ray->x, ray->y);
		if ((game->door_opening || game->door_closing) && ray->h_door_state == 0)
		{
			ray->h_door_state = moving_door_collision(game, ray);
			if (ray->h_door_state > 0)
				ray->door_h_dist = ray->distance_to_horizontal;
			if (ray->angle > PI)
				ray->door_h_col = ray->x - (int)(ray->x / TILE) * TILE;
			else
				ray->door_h_col = (int)(ray->x / TILE) * TILE + TILE - ray->x;
		}
		if (ray->distance_to_horizontal == MAX_DEPTH)
			return ;
	}
}

static void	vertical_intersection(t_game *game, t_ray *ray)
{
	ray->v_door_state = 0;
	ray->door_v_dist = MAX_DEPTH;
	if (ray->angle == PI / 2 || ray->angle == 3 * PI / 2)
	{
		ray->distance_to_vertical = MAX_DEPTH;
		return ;
	}
	else if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE) * TILE - 0.001;
		ray->y = game->p.y + ((game->p.x - ray->x) * (-1 * game->math.tan[(int)(ray->angle * game->math.trig_it)]));
		ray->x_step = -TILE;
		ray->y_step = TILE * (-1 * game->math.tan[(int)(ray->angle * game->math.trig_it)]);
	}
	else if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
	{
		ray->x = (int)(game->p.x / TILE) * TILE + TILE;
		ray->y = game->p.y + ((ray->x - game->p.x) * game->math.tan[(int)(ray->angle * game->math.trig_it)]);
		ray->x_step = TILE;
		ray->y_step = TILE * game->math.tan[(int)(ray->angle * game->math.trig_it)];
	}
	ray->distance_to_vertical = get_distance(game, ray->x, ray->y);
	if (game->door_opening || game->door_closing)
	{
		ray->v_door_state = moving_door_collision(game, ray);
		if (ray->v_door_state > 0)
			ray->door_v_dist = ray->distance_to_vertical;
		if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
			ray->door_v_col = ray->y - (int)(ray->y / TILE) * TILE;
		else
			ray->door_v_col = (int)(ray->y / TILE) * TILE + TILE - ray->y;
	}
	if (ray->distance_to_vertical == MAX_DEPTH)
		return ;
	while (wall_collision(game, ray->x, ray->y) == 0)
	{
		ray->x += ray->x_step;
		ray->y += ray->y_step;
		ray->distance_to_vertical = get_distance(game, ray->x, ray->y);
		if ((game->door_opening || game->door_closing) && ray->v_door_state == 0)
		{
			ray->v_door_state = moving_door_collision(game, ray);
			if (ray->v_door_state > 0)
				ray->door_v_dist = ray->distance_to_vertical;
			if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
				ray->door_v_col = ray->y - (int)(ray->y / TILE) * TILE;
			else
				ray->door_v_col = (int)(ray->y / TILE) * TILE + TILE - ray->y;
		}
		if (ray->distance_to_vertical == MAX_DEPTH)
			return ;
	}
}

void	cast_ray(t_game *game, t_ray *ray)
{
	ray->door = 0;
	ray->door_state = 0;
	ray->door_col = 0;
	ray->enemy_top = 0;
	ray->enemy_bottom = 0;
	horizontal_intersection(game, ray);
	if (ray->angle < PI)
	{
		ray->wall_side = NORTH;
		ray->col = (int)(ray->x / TILE) * TILE + TILE - ray->x;
	}
	else
	{
		ray->wall_side = SOUTH;
		ray->col = ray->x - (int)(ray->x / TILE) * TILE;
	}
	if (closed_door_collision(game, ray))
		ray->door = 1;
	vertical_intersection(game, ray);
	if (ray->distance_to_horizontal < ray->distance_to_vertical)
		ray->distance = ray->distance_to_horizontal;
	else
	{
		ray->distance = ray->distance_to_vertical;
		ray->col = ray->y;
		if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
		{
			ray->wall_side = WEST;
			ray->col = ray->y - (int)(ray->y / TILE) * TILE;
		}
		else
		{
			ray->wall_side = EAST;
			ray->col = (int)(ray->y / TILE) * TILE + TILE - ray->y;
		}
		if (closed_door_collision(game, ray))
			ray->door = 1;
	}
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
	game->z_buffer[ray->column] = ray->distance;
}
