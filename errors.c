/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:58 by jberay            #+#    #+#             */
/*   Updated: 2024/05/28 14:50:10 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_entry(t_error_entry *errors)
{
	errors[0] = (t_error_entry){MSG_MALLOC, MALLOC_ERR};
	errors[1] = (t_error_entry){MSG_ARG, ARG_ERR};
	errors[2] = (t_error_entry){MSG_FILE_EXT, FILE_EXT_ERR};
	errors[3] = (t_error_entry){MSG_FILE_OPEN, FILE_OPEN_ERR};
	errors[4] = (t_error_entry){MSG_SCENE_FORMAT, SCENE_FORMAT_ERR};
	errors[5] = (t_error_entry){MSG_INVALID_MAP, INVALID_MAP_ERR};
	errors[6] = (t_error_entry){MSG_MAP_NOT_CLOSED, MAP_NOT_CLOSED_ERR};
	errors[7] = (t_error_entry){MSG_INVALID_PLAYER, INVALID_PLAYER_ERR};
	errors[8] = (t_error_entry){MSG_MAP_BIG, MAP_BIG_ERR};
	errors[9] = (t_error_entry){MSG_ENEMIES, ENEMIES_ERR};
}

void	error_handler(t_scene *scene, t_err_code code)
{
	t_error_entry	errors[10];
	int				i;

	init_entry(errors);
	i = 0;
	while (i < 10)
	{
		if (errors[i].code == code)
		{
			if (scene)
				free_scene(scene);
			ft_putstr_fd(errors[i].message, 2);
			exit(code);
		}
		i++;
	}
}

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
	delete_enemy_textures(scene);
	delete_gun_hp_textures(scene);
}

void	mlx_error_exit(t_game *game, t_scene *scene)
{
	mlx_terminate(game->mlx);
	if (scene)
		delete_textures(scene);
	if (scene)
		free_scene(scene);
	exit(1);
}
