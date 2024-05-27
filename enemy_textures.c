/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:59:01 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/27 14:45:05 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	enemy_textures(t_game *game, t_scene *scene)
{
	int		i;
	int		e;

	e = 0;
	while (e < game->enemy_count)
	{
		i = 0;
		while (i < 9)
		{
			game->e[e].dimg[i] = enemy_death_img(game, scene, i);
			if (i < 4)
				game->e[e].img[i] = enemy_walk_img(game, scene, i);
			if (i < 3)
				game->e[e].aimg[i] = enemy_attack_img(game, scene, i);
			i++;
		}
		e++;
	}
}
