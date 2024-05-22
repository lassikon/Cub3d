/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/22 14:30:48 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_x(float *angle, int x)
{
	int	x_mid;

	x_mid = SCREEN_WIDTH / 2;
	if (x > SCREEN_WIDTH / 2)
	{
		*angle += (float)(x - x_mid) / MOUSE_SENSITIVITY;
		if (*angle > 2 * PI)
			*angle -= 2 * PI;
	}
	if (x < SCREEN_WIDTH / 2)
	{
		*angle -= (float)(x_mid - x) / MOUSE_SENSITIVITY;
		if (*angle < 0)
			*angle += 2 * PI;
	}
}

static void	move_y(float *center, int y)
{
	int	y_mid;

	y_mid = SCREEN_HEIGHT / 2;
	if (y > y_mid && *center > 0)
	{
		*center -= y - y_mid;
		if (*center < 0)
			*center = 0;
	}
	if (y < y_mid && *center < SCREEN_HEIGHT)
	{
		*center += y_mid - y;
		if (*center > SCREEN_HEIGHT)
			*center = SCREEN_HEIGHT;
	}
}

void	move_mouse(t_game *game)
{
	int	x;
	int	y;
	int	x_mid;
	int	y_mid;

	x = 0;
	y = 0;

	x_mid = SCREEN_WIDTH / 2;
	y_mid = SCREEN_HEIGHT / 2;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x > SCREEN_WIDTH)
		x = SCREEN_WIDTH;
	if (x < 0)
		x = 0;
	move_x(&game->p.angle, x);
	if (LOOK_UP_AND_DOWN)
		move_y(&game->vertical_center, y);
	mlx_set_mouse_pos(game->mlx, x_mid, y_mid);
}
