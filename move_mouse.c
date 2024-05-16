/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:44:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/16 15:27:23 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	weapons(t_game *game)
{
	int	flag;
	int aim_flag;
	int	i;

	i = 0;
	flag = 0;
	aim_flag = 0;
	// if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
	// {
	// 	game->sprite.hk53_idle_img->enabled = false;
	// 	game->sprite.hk53_fire_img[game->frame_count % 13]->enabled = true;
	// 	i++;
	// }


	if (game->weapon_aim)
		if(game->weapon_aim && game->frame_count - 1 >= 0)
			game->sprite.hk53_aim_mid_img[(game->frame_count - 1) % 11]->enabled = false;

	if (!game->weapon_aim)
		if(game->weapon_aim && game->frame_count - 1 >= 0)
			game->sprite.hk53_aim_mid_img[10 - (game->frame_count  % 11)]->enabled = false;
			

	while (i < 11)
	{
		if (game->sprite.hk53_aim_mid_img[i]->enabled)
			aim_flag = 1;
		i++;
	}
	if (game->frame_count % 11 == 0)
	{
		if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_RIGHT) && aim_flag == 0)
		{
			if (!game->weapon_aim)
				game->weapon_aim = 1;
			else
				game->weapon_aim = 0;
		}
	}

	
	if (game->weapon_aim && game->sprite.hk35_aim_idle_img->enabled == false)
	{
		game->sprite.hk53_aim_mid_img[game->frame_count % 11]->enabled = true;
	}
	else if (game->weapon_aim == 0 && game->sprite.hk35_aim_idle_img->enabled == true)
	{
		game->sprite.hk53_idle_img->enabled = false;
		game->sprite.hk53_aim_mid_img[10 - (game->frame_count % 11)]->enabled = true;
	}


	if (game->frame_count % 10 == 0)
	{
		if (aim_flag == 0 && game->weapon_aim)
			game->sprite.hk35_aim_idle_img->enabled = true;
		else if (aim_flag == 1 && game->weapon_aim == 0)
			game->sprite.hk35_aim_idle_img->enabled = false;
	}

	// if (game->frame_count - 1 >= 0)
	// 	game->sprite.hk53_fire_img[(game->frame_count - 1) % 13]->enabled = false;
	// while (i < 13)
	// {
	// 	if (game->sprite.hk53_fire_img[i]->enabled)
	// 		flag = 1;
	// 	i++;
	// }
	// if (!flag)
	// 	game->sprite.hk53_idle_img->enabled = true;
	printf("weapon aim: %d\n", game->weapon_aim);
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
