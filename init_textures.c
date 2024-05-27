/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:32:12 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/27 16:19:02 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	null_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		scene->ed_tex[i] = NULL;
		if (i < 4)
			scene->e_tex[i] = NULL;
		if (i < 3)
			scene->ea_tex[i] = NULL;
		i++;
	}
	scene->north_tex = NULL;
	scene->south_tex = NULL;
	scene->east_tex = NULL;
	scene->west_tex = NULL;
	scene->floor_tex = NULL;
	scene->ceiling_tex = NULL;
	scene->door_tex = NULL;
}

void	init_textures(t_game *game, t_scene *scene)
{
	null_textures(scene);
	load_textures(game, scene);
	wall_textures_to_img(game, scene);
	floor_ceiling_door_textures_to_img(game, scene);
	if (game->enemy_count > 0)
		enemy_textures(game, scene);
	delete_textures(scene);
}
