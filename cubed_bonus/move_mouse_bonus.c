/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 11:46:12 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

	if (game->over || game->victory)
		return ;
	x_mid = SCREEN_WIDTH / 2;
	y_mid = SCREEN_HEIGHT / 2;
	x = x_mid;
	y = y_mid;
	if (game->frame_count < 5)
		mlx_set_mouse_pos(game->mlx, x_mid, y_mid);
	if (game->frame_count < 5)
		return ;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x != x_mid || y != y_mid)
	{
		move_x(&game->p.angle, x);
		move_y(&game->vertical_center, y);
	}
	mlx_set_mouse_pos(game->mlx, x_mid, y_mid);
}
