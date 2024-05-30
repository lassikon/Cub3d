/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:59:01 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 11:06:29 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static mlx_image_t	*enemy_attack_img(t_game *game, t_scene *scene, int i)
{
	mlx_image_t	*img;
	char		buffer[100];

	get_texture_name(buffer, "sprites/enemy/attack", i);
	scene->ea_tex[i] = mlx_load_png(buffer);
	if (scene->ea_tex[i] == NULL)
		mlx_error_exit(game, scene);
	img = mlx_texture_to_image(game->mlx, scene->ea_tex[i]);
	if (img == NULL)
		mlx_error_exit(game, scene);
	if (mlx_resize_image(img, 64, 64) == false)
		mlx_error_exit(game, scene);
	return (img);
}

static mlx_image_t	*enemy_walk_img(t_game *game, t_scene *scene, int i)
{
	mlx_image_t	*img;
	char		buffer[100];

	get_texture_name(buffer, "sprites/enemy/walk", i);
	scene->e_tex[i] = mlx_load_png(buffer);
	if (scene->e_tex[i] == NULL)
		mlx_error_exit(game, scene);
	img = mlx_texture_to_image(game->mlx, scene->e_tex[i]);
	if (img == NULL)
		mlx_error_exit(game, scene);
	if (mlx_resize_image(img, 64, 64) == false)
		mlx_error_exit(game, scene);
	return (img);
}

static mlx_image_t	*enemy_death_img(t_game *game, t_scene *scene, int i)
{
	mlx_image_t	*img;
	char		buffer[100];

	get_texture_name(buffer, "sprites/enemy/death", i);
	scene->ed_tex[i] = mlx_load_png(buffer);
	if (scene->ed_tex[i] == NULL)
		mlx_error_exit(game, scene);
	img = mlx_texture_to_image(game->mlx, scene->ed_tex[i]);
	if (img == NULL)
		mlx_error_exit(game, scene);
	if (mlx_resize_image(img, 64, 64) == false)
		mlx_error_exit(game, scene);
	return (img);
}

static void	assign_enemy_textures(t_game *game)
{
	int		e;
	int		i;

	e = 1;
	while (e < game->enemy_count)
	{
		i = 0;
		while (i < 9)
		{
			game->e[e].dimg[i] = game->e[0].dimg[i];
			if (i < 4)
				game->e[e].img[i] = game->e[0].img[i];
			if (i < 3)
				game->e[e].aimg[i] = game->e[0].aimg[i];
			i++;
		}
		e++;
	}
}

void	enemy_textures(t_game *game, t_scene *scene)
{
	int		i;

	i = 0;
	while (i < 9)
	{
		game->e[0].dimg[i] = enemy_death_img(game, scene, i);
		if (i < 4)
			game->e[0].img[i] = enemy_walk_img(game, scene, i);
		if (i < 3)
			game->e[0].aimg[i] = enemy_attack_img(game, scene, i);
		i++;
	}
	assign_enemy_textures(game);
}
