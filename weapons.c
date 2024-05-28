/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:30:50 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/23 20:09:24 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	disable_img_frames(mlx_image_t **img, int frames)
{
	int	i;

	i = 0;
	while (i < frames)
	{
		img[i]->enabled = false;
		i++;
	}
}

void	fire_key(t_game *game, int *flag)
{
	disable_img_frames(game->gun.hk53_fire_img, 14);
	disable_img_frames(game->gun.hk53_fire_mid_img, 13);
	if ((mlx_is_key_down(game->mlx, MLX_KEY_F)
			|| mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		&& game->gun.state != AIM_ANIMATING)
	{
		game->gun.fire_frme++;
		*flag = 1;
	}
	if (*flag == 1 && game->gun.state == IDLE)
		game->gun.hk53_fire_img[game->gun.fire_frme % 14]->enabled = true;
	else if (*flag == 1 && game->gun.state == AIM)
		game->gun.hk53_fire_mid_img[game->gun.fire_frme % 13]->enabled = true;
	else if (*flag == 0 && game->gun.aim_frme < 1)
	{
		game->gun.hk53_fire_img[0]->enabled = true;
		game->gun.fire_frme = -1;
	}
	if (*flag && game->in_crosshairs_id >= 0
		&& game->e[game->in_crosshairs_id].dying == 0
		&& (game->gun.hk53_fire_img[0]->enabled == true
			|| game->gun.hk53_fire_mid_img[0]->enabled == true))
	{
		game->e[game->in_crosshairs_id].dying = 1;
		game->e[game->in_crosshairs_id].attacking = 0;
	}
}

void	aim_key(t_game *game, int *flag)
{
	disable_img_frames(game->gun.hk53_aim_mid_img, 12);
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		game->gun.hk53_fire_img[0]->enabled = false;
		if (game->gun.aim_frme < 11)
			game->gun.aim_frme++;
	}
	else
	{
		if (game->gun.aim_frme >= 0)
			game->gun.aim_frme--;
	}
	if (game->gun.aim_frme >= 0)
		game->gun.hk53_aim_mid_img[game->gun.aim_frme]->enabled = true;
	if (*flag)
		game->gun.hk53_aim_mid_img[11]->enabled = false;
	if (game->gun.hk53_aim_mid_img[11]->enabled == true)
		game->gun.fire_frme = -1;
}

void	weapons(t_game *game)
{
	int	flag;

	flag = 0;
	if (game->gun.aim_frme == -1)
		game->gun.state = IDLE;
	else if (game->gun.aim_frme == 11)
		game->gun.state = AIM;
	else
		game->gun.state = AIM_ANIMATING;
	fire_key(game, &flag);
	aim_key(game, &flag);
}
