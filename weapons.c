/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:30:50 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/23 14:29:09 by lkonttin         ###   ########.fr       */
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

void	fire(t_game *game, int *flag)
{
	disable_img_frames(game->sprite.hk53_fire_img, 14);
	disable_img_frames(game->sprite.hk53_fire_mid_img, 13);

	if ((mlx_is_key_down(game->mlx, MLX_KEY_F)
			|| mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		&& game->sprite.weapon_state != AIM_ANIMATING)
	{
		game->sprite.weapon_fire++;
		*flag = 1;
	}
	// printf("weapon_fire: %zu\n", game->sprite.weapon_fire);
	if (*flag == 1 && game->sprite.weapon_state == IDLE)
		game->sprite.hk53_fire_img[game->sprite.weapon_fire % 14]->enabled = true;
	else if (*flag == 1 && game->sprite.weapon_state == AIM)
		game->sprite.hk53_fire_mid_img[game->sprite.weapon_fire % 13]->enabled = true;
	else if (*flag == 0 && game->sprite.weapon_aim < 1)
	{
		game->sprite.hk53_fire_img[0]->enabled = true;
		game->sprite.weapon_fire = -1;
	}
	if (*flag && game->in_crosshairs_id >= 0
	&& (game->sprite.hk53_fire_img[1]->enabled == true || game->sprite.hk53_fire_mid_img[0]->enabled == true))
		game->e[game->in_crosshairs_id].alive = false;
}

void	weapons(t_game *game)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (game->sprite.weapon_aim == -1)
		game->sprite.weapon_state = IDLE;
	else if (game->sprite.weapon_aim == 11)
		game->sprite.weapon_state = AIM;
	else
		game->sprite.weapon_state = AIM_ANIMATING;

	fire(game, &flag);



	/*aim*/
	disable_img_frames(game->sprite.hk53_aim_mid_img, 12);
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
	if (game->sprite.weapon_aim >= 0)
		game->sprite.hk53_aim_mid_img[game->sprite.weapon_aim]->enabled = true;
	if (flag)
		game->sprite.hk53_aim_mid_img[11]->enabled = false;
	if (game->sprite.hk53_aim_mid_img[11]->enabled == true)
		game->sprite.weapon_fire = -1;
}
