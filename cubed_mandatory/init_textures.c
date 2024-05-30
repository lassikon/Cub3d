/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:25:52 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 10:21:24 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void	textures_to_images(t_game *game, t_scene *scene)
{
	game->north_img = mlx_texture_to_image(game->mlx, scene->north_tex);
	if (game->north_img == NULL)
	{
		delete_textures(scene);
		mlx_error_exit(game, scene);
	}
	game->south_img = mlx_texture_to_image(game->mlx, scene->south_tex);
	if (game->south_img == NULL)
	{
		delete_textures(scene);
		mlx_error_exit(game, scene);
	}
	game->east_img = mlx_texture_to_image(game->mlx, scene->east_tex);
	if (game->east_img == NULL)
	{
		delete_textures(scene);
		mlx_error_exit(game, scene);
	}
	game->west_img = mlx_texture_to_image(game->mlx, scene->west_tex);
	if (game->west_img == NULL)
	{
		delete_textures(scene);
		mlx_error_exit(game, scene);
	}
	delete_textures(scene);
}

void	init_textures(t_game *game, t_scene *scene)
{
	scene->north_tex = mlx_load_png(scene->no_texture);
	if (scene->north_tex == NULL)
		mlx_error_exit(game, scene);
	scene->south_tex = mlx_load_png(scene->so_texture);
	if (scene->south_tex == NULL)
	{
		delete_textures(scene);
		mlx_error_exit(game, scene);
	}
	scene->east_tex = mlx_load_png(scene->ea_texture);
	if (scene->east_tex == NULL)
	{
		delete_textures(scene);
		mlx_error_exit(game, scene);
	}
	scene->west_tex = mlx_load_png(scene->we_texture);
	if (scene->west_tex == NULL)
	{
		delete_textures(scene);
		mlx_error_exit(game, scene);
	}
	textures_to_images(game, scene);
}
