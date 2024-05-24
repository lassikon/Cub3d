/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:02:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/24 15:18:05 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_tx_and_ty(t_game *game, t_ray *ray)
{
	ray->ty = 0;
	ray->ty_step = (float)game->door_img->height / ray->height;
	if (game->render.top_wall < 0)
	{
		ray->ty += -game->render.top_wall * ray->ty_step;
		game->render.top_wall = 0;
		ray->height = SCREEN_HEIGHT;
	}
	ray->tx = (float)(game->door_img->width / TILE_SIZE)
		* (ray->door_col + 5 * ray->door_state);
	if (ray->tx >= game->door_img->width)
		return ;
	ray->tx = fmod(ray->tx, game->door_img->width);
	ray->ty = fmod(ray->ty, game->door_img->height);
}

static void	draw_moving_door(t_game *game, t_ray *ray)
{
	int	row;

	calc_tx_and_ty(game, ray);
	if (ray->tx >= game->door_img->width)
		return ;
	row = 0;
	game->render.brightness = 1;
	while (row < ray->height)
	{
		put_texture_pixel(game, ray, game->door_img,
			game->render.top_wall + row);
		row++;
		ray->ty += ray->ty_step;
		if (ray->ty >= game->door_img->height)
			break ;
	}
}

static void	render_moving_door(t_game *game, t_ray *ray)
{
	float		ratio;
	int			fishtable;

	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	ray->door_distance *= game->math.fishcos[fishtable];
	ratio = game->dist_to_proj_plane / ray->door_distance;
	game->render.bottom_wall = (ratio * game->p.height) + game->vertical_center;
	ray->height = (game->dist_to_proj_plane * WALL_HEIGHT) / ray->door_distance;
	game->render.top_wall = game->render.bottom_wall - (int)ray->height;
	draw_moving_door(game, ray);
}

void	moving_door(t_game *game)
{
	int	i;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		if (game->rays[i].door_state)
		{
			if (game->rays[i].door_distance < game->rays[i].distance)
				render_moving_door(game, &game->rays[i]);
		}
		i++;
	}
	update_door_state(game);
}
