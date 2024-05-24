/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:09:23 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/24 15:10:05 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

void	put_texture_pixel(t_game *game, t_ray *ray, mlx_image_t *img, int row)
{
	int	color;
	int	red;
	int	green;
	int	blue;
	int	alpha;

	ray->pixel = &img->pixels[(int)ray->ty * img->width * 4 + (int)ray->tx * 4];
	if (ray->pixel[3] != 0)
	{
		red = ray->pixel[0] * game->render.brightness;
		green = ray->pixel[1] * game->render.brightness;
		blue = ray->pixel[2] * game->render.brightness;
		alpha = ray->pixel[3];
		color = get_rgba(red, green, blue, alpha);
		mlx_put_pixel(game->image, ray->column, row, color);
	}
}

void	get_brightness_lvl(t_game *game, t_ray *ray)
{
	if (ray->wall_side == EAST || ray->wall_side == WEST)
		game->render.brightness = 180 / ray->distance;
	else
		game->render.brightness = 130 / ray->distance;
	if (game->render.brightness > 1)
		game->render.brightness = 1;
	if (game->render.brightness < 0.1)
		game->render.brightness = 0.1;
}
