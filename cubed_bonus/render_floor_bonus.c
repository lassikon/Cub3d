/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:14 by jberay            #+#    #+#             */
/*   Updated: 2024/05/30 11:07:45 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_floor_color(t_game *game)
{
	int		x;
	int		y;
	int		color;
	float	b;

	y = game->vertical_center;
	while (y < SCREEN_HEIGHT)
	{
		b = (y - game->vertical_center + 150) / SCREEN_HEIGHT;
		if (b > 1)
			b = 1;
		if (b < 0)
			b = 0;
		color = get_rgba(game->floor_color[0] * b, game->floor_color[1] * b, \
			game->floor_color[2] * b, 255);
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		y++;
	}
}

static void	get_floor_ray_x_y(t_game *game, t_ray *ray, int row)
{
	float	eye_to_floor;
	float	ratio;
	float	angle;
	int		fishtable;
	int		trigtable;

	if (row - game->vertical_center <= 0)
		return ;
	ratio = game->p.height / (row - game->vertical_center);
	fishtable = (int)(fabs(game->p.angle - ray->angle) * game->math.fish_it);
	trigtable = (int)(ray->angle * game->math.trig_it);
	angle = game->math.ifishcos[fishtable];
	eye_to_floor = ratio * game->dist_to_proj_plane * angle;
	ray->tx = game->p.x + game->math.cos[trigtable] * eye_to_floor;
	ray->ty = game->p.y + game->math.sin[trigtable] * eye_to_floor;
	game->render.brightness = 150 / eye_to_floor;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
}

void	draw_floor(t_game *game, t_ray *ray, mlx_image_t *img)
{
	int		row;

	if (!img)
		return ;
	row = (int)game->render.bottom_wall;
	while (row < SCREEN_HEIGHT)
	{
		get_floor_ray_x_y(game, ray, row);
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
		row++;
		if (row >= SCREEN_HEIGHT)
			break ;
		put_texture_pixel(game, ray, img, row);
		row++;
	}
}
