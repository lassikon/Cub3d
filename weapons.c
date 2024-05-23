/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:30:50 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/23 10:31:26 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* int	enemy_hit(t_game *game)
{
	int crosshair_x;
	int crosshair_y;

	crosshair_x= SCREEN_WIDTH / 2;
	crosshair_y = SCREEN_HEIGHT / 2;
	if (game->rays[crosshair_x].enemy_top)
	{
		if (game->rays[crosshair_x].enemy_top < crosshair_y
			&& game->rays[crosshair_x].enemy_bottom > crosshair_y)
			return (1);
	}
	return (0);
} */

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
		game->sprite.weapon_state = ANIMATING;
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

	if ((mlx_is_key_down(game->mlx, MLX_KEY_F) 
		|| mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		&& game->sprite.weapon_state != ANIMATING)
	{
		game->sprite.weapon_fire++;
		flag = 1;
		if (game->in_crosshairs_id >= 0)
			game->e[game->in_crosshairs_id].alive = false;
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
	if (game->sprite.weapon_aim >= 0)
		game->sprite.hk53_aim_mid_img[game->sprite.weapon_aim]->enabled = true;
	if (flag)
		game->sprite.hk53_aim_mid_img[11]->enabled = false;
}
