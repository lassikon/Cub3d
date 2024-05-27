/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:32:12 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/27 11:04:25 by lkonttin         ###   ########.fr       */
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

static void	enemy_walk_textures_to_img(t_game *game, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		game->e[i].img[0] = mlx_texture_to_image(game->mlx, scene->e_tex[0]);
		if (game->e[i].img[0] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].img[1] = mlx_texture_to_image(game->mlx, scene->e_tex[1]);
		if (game->e[i].img[1] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].img[2] = mlx_texture_to_image(game->mlx, scene->e_tex[2]);
		if (game->e[i].img[2] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].img[3] = mlx_texture_to_image(game->mlx, scene->e_tex[3]);
		if (game->e[i].img[3] == NULL)
			mlx_error_exit(game, scene);
		i++;
	}
}

static void	enemy_death_textures_to_img(t_game *game, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		game->e[i].dimg[0] = mlx_texture_to_image(game->mlx, scene->ed_tex[0]);
		if (game->e[i].dimg[0] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].dimg[1] = mlx_texture_to_image(game->mlx, scene->ed_tex[1]);
		if (game->e[i].dimg[1] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].dimg[2] = mlx_texture_to_image(game->mlx, scene->ed_tex[2]);
		if (game->e[i].dimg[2] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].dimg[3] = mlx_texture_to_image(game->mlx, scene->ed_tex[3]);
		if (game->e[i].dimg[3] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].dimg[4] = mlx_texture_to_image(game->mlx, scene->ed_tex[4]);
		if (game->e[i].dimg[4] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].dimg[5] = mlx_texture_to_image(game->mlx, scene->ed_tex[5]);
		if (game->e[i].dimg[5] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].dimg[6] = mlx_texture_to_image(game->mlx, scene->ed_tex[6]);
		if (game->e[i].dimg[6] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].dimg[7] = mlx_texture_to_image(game->mlx, scene->ed_tex[7]);
		if (game->e[i].dimg[7] == NULL)
			mlx_error_exit(game, scene);
		game->e[i].dimg[8] = mlx_texture_to_image(game->mlx, scene->ed_tex[8]);
		if (game->e[i].dimg[8] == NULL)
			mlx_error_exit(game, scene);
		i++;
	}
}

static void	resize_enemy_walk_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (mlx_resize_image(game->e[i].img[0], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].img[1], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].img[2], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].img[3], 64, 64) == false)
			mlx_error_exit(game, NULL);
		i++;
	}
}

static void	resize_enemy_death_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (mlx_resize_image(game->e[i].dimg[0], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].dimg[1], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].dimg[2], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].dimg[3], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].dimg[4], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].dimg[5], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].dimg[6], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].dimg[7], 64, 64) == false)
			mlx_error_exit(game, NULL);
		if (mlx_resize_image(game->e[i].dimg[8], 64, 64) == false)
			mlx_error_exit(game, NULL);
		i++;
	}

}

void	init_textures(t_game *game, t_scene *scene)
{
	load_textures(game, scene);
	wall_textures_to_img(game, scene);
	floor_ceiling_door_textures_to_img(game, scene);
	enemy_walk_textures_to_img(game, scene);
	enemy_death_textures_to_img(game, scene);
	delete_textures(scene);
	resize_enemy_walk_images(game);
	resize_enemy_death_images(game);
}
