/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:32:12 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 11:06:55 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	wall_textures_to_img(t_game *game, t_scene *scene)
{
	game->north_img = mlx_texture_to_image(game->mlx, scene->north_tex);
	if (game->north_img == NULL)
		mlx_error_exit(game, scene);
	game->south_img = mlx_texture_to_image(game->mlx, scene->south_tex);
	if (game->south_img == NULL)
		mlx_error_exit(game, scene);
	game->east_img = mlx_texture_to_image(game->mlx, scene->east_tex);
	if (game->east_img == NULL)
		mlx_error_exit(game, scene);
	game->west_img = mlx_texture_to_image(game->mlx, scene->west_tex);
	if (game->west_img == NULL)
		mlx_error_exit(game, scene);
	if (mlx_resize_image(game->north_img, 512, 512) == false)
		mlx_error_exit(game, scene);
	if (mlx_resize_image(game->south_img, 512, 512) == false)
		mlx_error_exit(game, scene);
	if (mlx_resize_image(game->east_img, 512, 512) == false)
		mlx_error_exit(game, scene);
	if (mlx_resize_image(game->west_img, 512, 512) == false)
		mlx_error_exit(game, scene);
}

static void	floor_ceiling_door_textures_to_img(t_game *game, t_scene *scene)
{
	if (scene->floor_tex)
	{
		game->floor_img = mlx_texture_to_image(game->mlx, scene->floor_tex);
		if (game->floor_img == NULL)
			mlx_error_exit(game, scene);
		if (mlx_resize_image(game->floor_img, 512, 512) == false)
			mlx_error_exit(game, scene);
	}
	if (scene->ceiling_tex)
	{
		game->ceiling_img = mlx_texture_to_image(game->mlx, scene->ceiling_tex);
		if (game->ceiling_img == NULL)
			mlx_error_exit(game, scene);
		if (mlx_resize_image(game->ceiling_img, 512, 512) == false)
			mlx_error_exit(game, scene);
	}
	if (scene->door_tex)
	{
		game->door_img = mlx_texture_to_image(game->mlx, scene->door_tex);
		if (game->door_img == NULL)
			mlx_error_exit(game, scene);
		if (mlx_resize_image(game->door_img, 512, 512) == false)
			mlx_error_exit(game, scene);
	}
}

static void	null_e_and_w_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < 14)
	{
		scene->hk53_fire_tx[i] = NULL;
		if (i < 10)
			scene->hp_txs[i] = NULL;
		if (i < 13)
			scene->hk53_fire_mid_tx[i] = NULL;
		if (i < 12)
			scene->hk53_aim_mid_tx[i] = NULL;
		if (i < 9)
			scene->ed_tex[i] = NULL;
		if (i < 4)
			scene->e_tex[i] = NULL;
		if (i < 3)
			scene->ea_tex[i] = NULL;
		i++;
	}
}

void	init_textures(t_game *game, t_scene *scene)
{
	scene->north_tex = NULL;
	scene->south_tex = NULL;
	scene->east_tex = NULL;
	scene->west_tex = NULL;
	scene->floor_tex = NULL;
	scene->ceiling_tex = NULL;
	scene->door_tex = NULL;
	scene->game_over_tex = NULL;
	null_e_and_w_textures(scene);
	load_textures(game, scene);
	wall_textures_to_img(game, scene);
	floor_ceiling_door_textures_to_img(game, scene);
	if (game->enemy_count > 0)
		enemy_textures(game, scene);
	delete_textures(scene);
}
