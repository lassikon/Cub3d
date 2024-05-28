/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:09:23 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/28 11:58:53 by lkonttin         ###   ########.fr       */
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

void	next_enemy_to_render(t_game *game)
{
	int		i;
	float	rel_x;
	float	rel_y;
	float	distance;

	i = 0;
	distance = 0;
	game->next_enemy_to_render = -1;
	while (i < game->enemy_count)
	{
		if (game->e[i].rendered == false && game->e[i].alive == true)
		{
			rel_x = game->e[i].x - game->p.x;
			rel_y = game->e[i].y - game->p.y;
			game->e[i].distance = sqrtf(rel_x * rel_x + rel_y * rel_y);
			if (game->e[i].distance > distance)
			{
				distance = game->e[i].distance;
				game->next_enemy_to_render = i;
			}
		}
		i++;
	}
	if (game->next_enemy_to_render >= 0)
		enemy_attack(game, game->next_enemy_to_render);
}
