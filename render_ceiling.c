/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:06:34 by jberay            #+#    #+#             */
/*   Updated: 2024/05/24 15:00:59 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ceiling_color(t_game *game)
{
	int		x;
	int		y;
	int		color;
	float	b;

	y = 0;
	while (y <= game->vertical_center)
	{
		b = (game->vertical_center + 1) / (y + (float)game->vertical_center);
		if (b > 1)
			b = 1;
		if (b < 0)
			b = 0;
		x = 0;
		color = get_rgba(game->ceiling_color[0] * b, \
			game->ceiling_color[1] * b, game->ceiling_color[2] * b, 255);
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		y++;
	}
}

static void	get_ceiling_ray_x_y(t_game *game, t_ray *ray, int row)
{
	float	eye_to_floor;
	float	ratio;
	float	angle;
	int		fishtable;
	int		trigtable;

	if (game->vertical_center - row <= 0)
		return ;
	ratio = (WALL_HEIGHT - game->p.height) / (game->vertical_center - row);
	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	trigtable = (int)(ray->angle * game->math.trig_it);
	angle = game->math.ifishcos[fishtable];
	eye_to_floor = ratio * game->dist_to_proj_plane * angle;
	ray->tx = game->p.x + game->math.cos[trigtable] * eye_to_floor;
	ray->ty = game->p.y + game->math.sin[trigtable] * eye_to_floor;
	game->render.brightness = 100 / eye_to_floor;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
}

void	draw_ceiling(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int		row;

	if (!img)
		return ;
	row = (int)game->render.top_wall;
	while (row >= 0)
	{
		get_ceiling_ray_x_y(game, ray, row);
		if (ray->tx < 0)
			ray->tx += TILE_SIZE;
		if (ray->ty < 0)
			ray->ty += TILE_SIZE;
		ray->tx = ray->tx - (int)(ray->tx / TILE_SIZE) * TILE_SIZE;
		ray->ty = ray->ty - (int)(ray->ty / TILE_SIZE) * TILE_SIZE;
		ray->tx = (float)img->width / TILE_SIZE * ray->tx;
		ray->ty = (float)img->height / TILE_SIZE * ray->ty;
		ray->tx = ((int)ray->tx % img->width);
		ray->ty = ((int)ray->ty % img->height);
		put_texture_pixel(game, ray, img, row);
		row--;
	}
}
