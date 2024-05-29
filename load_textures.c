/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:42:55 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/29 11:30:23 by lkonttin         ###   ########.fr       */
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

static void	load_hp_textures(t_game *game, t_scene *scene)
{
	int		i;
	char	buffer[100];

	i = 0;
	while (i < 10)
	{
		get_texture_name(buffer, "textures/hp/blood", 1 + i);
		scene->hp_txs[i] = mlx_load_png(buffer);
		if (scene->hp_txs[i] == NULL)
			mlx_error_exit(game, scene);
		game->hp_imgs[i] = mlx_texture_to_image(game->mlx, \
		scene->hp_txs[i]);
		mlx_resize_image(game->hp_imgs[i], \
		SCREEN_WIDTH, SCREEN_HEIGHT);
		mlx_image_to_window(game->mlx, game->hp_imgs[i], 0, 0);
		mlx_set_instance_depth(&game->hp_imgs[i]->instances[0], \
		3);
		game->hp_imgs[i]->enabled = true;
		i++;
	}
}

static void	load_end_screens(t_game *game, t_scene *scene)
{
	scene->game_over_tex = mlx_load_png("textures/game_over.png");
	if (scene->game_over_tex == NULL)
		mlx_error_exit(game, scene);
	game->game_over_img = mlx_texture_to_image(game->mlx, \
	scene->game_over_tex);
	if (game->game_over_img == NULL)
		mlx_error_exit(game, scene);
	mlx_image_to_window(game->mlx, game->game_over_img, 0, 0);
	mlx_set_instance_depth(&game->game_over_img->instances[0], 4);
	game->game_over_img->instances[0].enabled = false;
	scene->win_tex = mlx_load_png("textures/win.png");
	if (scene->win_tex == NULL)
		mlx_error_exit(game, scene);
	game->win_img = mlx_texture_to_image(game->mlx, scene->win_tex);
	if (game->win_img == NULL)
		mlx_error_exit(game, scene);
	mlx_image_to_window(game->mlx, game->win_img, 0, 0);
	mlx_set_instance_depth(&game->win_img->instances[0], 4);
	game->win_img->instances[0].enabled = false;
}

void	load_textures(t_game *game, t_scene *scene)
{
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
	load_end_screens(game, scene);
}
