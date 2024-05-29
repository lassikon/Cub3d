/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:09:23 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/29 15:49:19 by lkonttin         ###   ########.fr       */
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

void	get_enemy_tx_ty(t_game *game, t_ray *eray, float ratio, int i)
{
	eray->ty = 0;
	eray->ty_step = (float)game->e[i].img[0]->height / eray->height;
	game->render.e_bottom = (ratio * game->p.height) + game->vertical_center;
	game->render.e_top = game->render.e_bottom - eray->height;
	if (game->render.e_top < 0)
	{
		eray->ty += -game->render.e_top * eray->ty_step;
		game->render.e_top = 0;
	}
	if (game->render.e_bottom >= SCREEN_HEIGHT)
		game->render.e_bottom = SCREEN_HEIGHT - 1;
	eray->ty_step = fmod(eray->ty_step, game->e[i].img[0]->height);
	eray->tx_step = (float)game->e[i].img[0]->width / eray->height;
	eray->tx = 0;
	game->render.e_left = -eray->height / 2 + eray->sprite_screen_x;
	game->render.e_right = eray->height / 2 + eray->sprite_screen_x;
	if (game->render.e_left < 0)
	{
		eray->tx += -game->render.e_left * eray->tx_step;
		game->render.e_left = 0;
	}
	if (game->render.e_right >= SCREEN_WIDTH)
		game->render.e_right = SCREEN_WIDTH - 1;
	eray->tx_step = fmod(eray->tx_step, game->e[i].img[0]->width);
}

void	get_enemy_x_y(t_game *game, t_ray *eray, int i)
{
	float	rel_x;
	float	rel_y;
	int		trigtable;
	float	ratio;

	trigtable = (int)(game->p.angle * game->math.trig_it);
	rel_x = game->e[i].x - game->p.x;
	rel_y = game->e[i].y - game->p.y;
	eray->x = rel_y * game->math.cos[trigtable] \
		- rel_x * game->math.sin[trigtable];
	eray->y = rel_y * game->math.sin[trigtable] \
		+ rel_x * game->math.cos[trigtable];
	eray->distance = sqrtf(eray->x * eray->x + eray->y * eray->y);
	if (eray->y <= 0)
		return ;
	ratio = game->dist_to_proj_plane / eray->distance;
	eray->sprite_screen_x = (int)((SCREEN_WIDTH / 2) \
		+ ((eray->x * game->dist_to_proj_plane) / eray->y));
	eray->height = (int)((E_HEIGHT / eray->distance) \
		* game->dist_to_proj_plane);
	eray->wall_side = NORTH;
	get_enemy_tx_ty(game, eray, ratio, i);
}
