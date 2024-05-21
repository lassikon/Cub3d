/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:57:27 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/21 14:02:10 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

static void	render_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	color = get_rgba(game->ceiling_color[0], game->ceiling_color[1],
			game->ceiling_color[2], 255);
	while (y <= game->vertical_center)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		y++;
	}
}

static void	render_floor(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = game->vertical_center;
	color = get_rgba(game->floor_color[0], game->floor_color[1],
			game->floor_color[2], 255);
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		y++;
	}
}

void	render(t_game *game)
{
	t_ray	ray;
	float	angle_step;

	ray.column = 0;
	angle_step = FOV / SCREEN_WIDTH;
	ray.angle = game->p.angle - FOV / 2;
	render_ceiling(game);
	render_floor(game);
	while (ray.column < SCREEN_WIDTH)
	{
		if (ray.angle < 0)
			ray.angle += 2 * PI;
		else if (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		cast_ray(game, &ray);
		if (ray.distance < MAX_DEPTH)
			render_wall_column(game, &ray);
		ray.column++;
		ray.angle += angle_step;
	}
}
