/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/16 19:48:34 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	weapons(t_game *game)
{
	int	i;
	int flag;

	i = 0;
	flag = 0;
	if (game->sprite.weapon_aim == -1)
		game->sprite.weapon_state = IDLE;
	while (i < 14)
	{
		game->sprite.hk53_fire_img[i]->enabled = false;
		i++;
	}
	i = 0;
	while (i < 13)
	{
		game->sprite.hk53_fire_mid_img[i]->enabled = false;
		i++;
	}
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		game->sprite.weapon_fire++;
		flag = 1;
	}
	if (flag == 1 && game->sprite.weapon_state == IDLE)
		game->sprite.hk53_fire_img[game->sprite.weapon_fire % 14]->enabled = true;
	else if (flag == 1 && game->sprite.weapon_state == AIM)
		game->sprite.hk53_fire_mid_img[game->sprite.weapon_fire % 13]->enabled = true;
	else if (flag == 0 && game->sprite.weapon_aim < 1)
		game->sprite.hk53_fire_img[0]->enabled = true;

	/*aim*/
	i = 0;
	while (i < 12)
	{
		game->sprite.hk53_aim_mid_img[i]->enabled = false;
		i++;
	}
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		game->sprite.weapon_state = AIM;
		game->sprite.hk53_fire_img[0]->enabled = false;
		if (game->sprite.weapon_aim < 11)
			game->sprite.weapon_aim++;
	}
	else
	{
		if (game->sprite.weapon_aim >= 0)
			game->sprite.weapon_aim--;
	}
	if (game->sprite.weapon_aim >= 0 && !mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		game->sprite.hk53_aim_mid_img[game->sprite.weapon_aim]->enabled = true;

	/*reload*/
}

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
