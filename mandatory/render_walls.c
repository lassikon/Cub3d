/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/21 14:08:09 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	fishbowl(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (cos(angle));
}

static void	draw_column(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int	y;
	int	color;

	ray->ty_step = (float)IMG_HEIGHT / ray->height;
	ray->ty = 0;
	if (ray->height > SCREEN_HEIGHT)
	{
		ray->ty += (ray->height - SCREEN_HEIGHT) / 2 * ray->ty_step;
		ray->height = SCREEN_HEIGHT;
	}
	y = game->vertical_center - ray->height / 2;
	ray->tx = (int)(ray->col * (float)(IMG_WIDTH / TILE)) * 4;
	while (y < game->vertical_center + ray->height / 2 && y < SCREEN_HEIGHT)
	{
		ray->pix = &img->pixels[(int)ray->ty * IMG_WIDTH * 4 + ray->tx];
		if (!ray->pix[3])
			break ;
		color = get_rgba(ray->pix[0], ray->pix[1], ray->pix[2], ray->pix[3]);
		mlx_put_pixel(game->image, ray->column, y, color);
		y++;
		ray->ty += ray->ty_step;
		if (ray->ty >= IMG_HEIGHT)
			break ;
	}
}

void	render_wall_column(t_game *game, t_ray *ray)
{
	ray->distance *= fishbowl(game->p.angle - ray->angle);
	ray->height = (int)(TILE / ray->distance * game->dist_to_proj_plane);
	if (ray->wall_side == NORTH)
		draw_column(game, ray, game->north_img);
	else if (ray->wall_side == SOUTH)
		draw_column(game, ray, game->south_img);
	else if (ray->wall_side == EAST)
		draw_column(game, ray, game->east_img);
	else if (ray->wall_side == WEST)
		draw_column(game, ray, game->west_img);
}
