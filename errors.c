/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:58 by jberay            #+#    #+#             */
/*   Updated: 2024/05/27 12:54:35 by lkonttin         ###   ########.fr       */
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
	errors[7] = (t_error_entry){MSG_INVALID_MAP, INVALID_PLAYER_ERR};
	errors[8] = (t_error_entry){MSG_MAP_BIG, MAP_BIG_ERR};
}

void	error_handler(t_scene *scene, t_err_code code)
{
	t_error_entry	errors[9];
	int				i;

	init_entry(errors);
	i = 0;
	while (i < 9)
	{
		if (errors[i].code == code)
		{
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
	while (i < 4)
	{
		if (scene->e_tex[i])
			mlx_delete_texture(scene->e_tex[i]);
		i++;
	}
	i = 0;
	while (i < 9)
	{
		if (scene->ed_tex[i])
			mlx_delete_texture(scene->ed_tex[i]);
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
