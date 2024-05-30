/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_textures_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:41:14 by jberay            #+#    #+#             */
/*   Updated: 2024/05/30 11:06:24 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	delete_enemy_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (scene->ed_tex[i])
			mlx_delete_texture(scene->ed_tex[i]);
		if (i < 4)
		{
			if (scene->e_tex[i])
				mlx_delete_texture(scene->e_tex[i]);
		}
		if (i < 3)
		{
			if (scene->ea_tex[i])
				mlx_delete_texture(scene->ea_tex[i]);
		}
		i++;
	}
}

static void	delete_gun_hp_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < 14)
	{
		if (scene->hk53_fire_tx[i])
			mlx_delete_texture(scene->hk53_fire_tx[i]);
		if (i < 12)
		{
			if (scene->hk53_aim_mid_tx[i])
				mlx_delete_texture(scene->hk53_aim_mid_tx[i]);
		}
		if (i < 13)
		{
			if (scene->hk53_fire_mid_tx[i])
				mlx_delete_texture(scene->hk53_fire_mid_tx[i]);
		}
		if (i < 10)
		{
			if (scene->hp_txs[i])
				mlx_delete_texture(scene->hp_txs[i]);
		}
		i++;
	}
}

void	delete_textures(t_scene *scene)
{
	if (scene->north_tex)
		mlx_delete_texture(scene->north_tex);
	if (scene->south_tex)
		mlx_delete_texture(scene->south_tex);
	if (scene->east_tex)
		mlx_delete_texture(scene->east_tex);
	if (scene->west_tex)
		mlx_delete_texture(scene->west_tex);
	if (scene->floor_tex)
		mlx_delete_texture(scene->floor_tex);
	if (scene->ceiling_tex)
		mlx_delete_texture(scene->ceiling_tex);
	if (scene->door_tex)
		mlx_delete_texture(scene->door_tex);
	if (scene->game_over_tex)
		mlx_delete_texture(scene->game_over_tex);
	delete_enemy_textures(scene);
	delete_gun_hp_textures(scene);
}
