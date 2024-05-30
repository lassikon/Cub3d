/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:23:50 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 11:07:35 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

float	get_distance(t_game *game, float dx, float dy)
{
	if (dx < 0 || dx > game->map_width || (dy < 0 || dy > game->map_height))
		return (MAX_DEPTH);
	return (sqrt(((game->p.x - dx) * (game->p.x - dx))
			+ ((game->p.y - dy) * (game->p.y - dy))));
}

void	init_ray(t_ray *ray)
{
	ray->distance_to_horizontal = MAX_DEPTH;
	ray->distance_to_vertical = MAX_DEPTH;
	ray->h_door_state = 0;
	ray->v_door_state = 0;
	ray->door_state = 0;
	ray->door_h_dist = MAX_DEPTH;
	ray->door_v_dist = MAX_DEPTH;
	ray->wall_side = 0;
	ray->x = 0;
	ray->y = 0;
	ray->x_step = 0;
	ray->y_step = 0;
}
