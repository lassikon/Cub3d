/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:42:55 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/28 11:13:46 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_wall_textures(t_game *game, t_scene *scene)
{
	scene->north_tex = mlx_load_png(scene->no_texture);
	if (scene->north_tex == NULL)
		mlx_error_exit(game, scene);
	scene->south_tex = mlx_load_png(scene->so_texture);
	if (scene->south_tex == NULL)
		mlx_error_exit(game, scene);
	scene->east_tex = mlx_load_png(scene->ea_texture);
	if (scene->east_tex == NULL)
		mlx_error_exit(game, scene);
	scene->west_tex = mlx_load_png(scene->we_texture);
	if (scene->west_tex == NULL)
		mlx_error_exit(game, scene);
}

static void	load_floor_ceiling_door_textures(t_game *game, t_scene *scene)
{
	if (scene->fl_texture)
	{
		scene->floor_tex = mlx_load_png(scene->fl_texture);
		if (scene->floor_tex == NULL)
			mlx_error_exit(game, scene);
	}
	if (scene->cl_texture)
	{
		scene->ceiling_tex = mlx_load_png(scene->cl_texture);
		if (scene->ceiling_tex == NULL)
			mlx_error_exit(game, scene);
	}
	if (scene->dr_texture)
	{
		scene->door_tex = mlx_load_png(scene->dr_texture);
		if (scene->door_tex == NULL)
			mlx_error_exit(game, scene);
	}
}

void	load_hp_textures(t_game *game, t_scene *scene)
{
	int		i;
	char	buffer[100];

	i = 0;
	while (i < 10)
	{
		get_texture_name(buffer, "textures/hp/blood", 1 + i);
		game->hp_txs[i] = mlx_load_png(buffer);
		if (game->hp_txs[i] == NULL)
			mlx_error_exit(game, scene);
		game->hp_imgs[i] = mlx_texture_to_image(game->mlx, \
		game->hp_txs[i]);
		mlx_resize_image(game->hp_imgs[i], \
		SCREEN_WIDTH, SCREEN_HEIGHT);
		mlx_image_to_window(game->mlx, game->hp_imgs[i], 0, 0);
		mlx_set_instance_depth(&game->hp_imgs[i]->instances[0], \
		3);
		game->hp_imgs[i]->enabled = true;
		i++;
	}
}

void	load_textures(t_game *game, t_scene *scene)
{
	scene->north_tex = NULL;
	scene->south_tex = NULL;
	scene->east_tex = NULL;
	scene->west_tex = NULL;
	scene->floor_tex = NULL;
	scene->ceiling_tex = NULL;
	scene->door_tex = NULL;
	game->north_img = NULL;
	game->south_img = NULL;
	game->east_img = NULL;
	game->west_img = NULL;
	game->floor_img = NULL;
	game->ceiling_img = NULL;
	game->door_img = NULL;
	load_hp_textures(game, scene);
	load_wall_textures(game, scene);
	load_floor_ceiling_door_textures(game, scene);
	load_weapon_textures(game, scene);
}
