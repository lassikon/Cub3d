/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:42:55 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/27 11:02:28 by lkonttin         ###   ########.fr       */
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

static void	load_enemy_walk_textures(t_game *game, t_scene *scene)
{
	scene->e_tex[0] = mlx_load_png("sprites/enemy/walk1.png");
	if (scene->e_tex[0] == NULL)
		mlx_error_exit(game, scene);
	scene->e_tex[1] = mlx_load_png("sprites/enemy/walk2.png");
	if (scene->e_tex[1] == NULL)
		mlx_error_exit(game, scene);
	scene->e_tex[2] = mlx_load_png("sprites/enemy/walk3.png");
	if (scene->e_tex[2] == NULL)
		mlx_error_exit(game, scene);
	scene->e_tex[3] = mlx_load_png("sprites/enemy/walk4.png");
	if (scene->e_tex[3] == NULL)
		mlx_error_exit(game, scene);
}

static void	load_enemy_d_textures(t_game *game, t_scene *scene)
{
	scene->ed_tex[0] = mlx_load_png("sprites/enemy/death1.png");
	if (scene->ed_tex[0] == NULL)
		mlx_error_exit(game, scene);
	scene->ed_tex[1] = mlx_load_png("sprites/enemy/death2.png");
	if (scene->ed_tex[1] == NULL)
		mlx_error_exit(game, scene);
	scene->ed_tex[2] = mlx_load_png("sprites/enemy/death3.png");
	if (scene->ed_tex[2] == NULL)
		mlx_error_exit(game, scene);
	scene->ed_tex[3] = mlx_load_png("sprites/enemy/death4.png");
	if (scene->ed_tex[3] == NULL)
		mlx_error_exit(game, scene);
	scene->ed_tex[4] = mlx_load_png("sprites/enemy/death5.png");
	if (scene->ed_tex[4] == NULL)
		mlx_error_exit(game, scene);
	scene->ed_tex[5] = mlx_load_png("sprites/enemy/death6.png");
	if (scene->ed_tex[5] == NULL)
		mlx_error_exit(game, scene);
	scene->ed_tex[6] = mlx_load_png("sprites/enemy/death7.png");
	if (scene->ed_tex[6] == NULL)
		mlx_error_exit(game, scene);
	scene->ed_tex[7] = mlx_load_png("sprites/enemy/death8.png");
	if (scene->ed_tex[7] == NULL)
		mlx_error_exit(game, scene);
	scene->ed_tex[8] = mlx_load_png("sprites/enemy/death9.png");
	if (scene->ed_tex[8] == NULL)
		mlx_error_exit(game, scene);
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
	load_wall_textures(game, scene);
	load_floor_ceiling_door_textures(game, scene);
	load_weapon_textures(game, scene);
	load_enemy_walk_textures(game, scene);
	load_enemy_d_textures(game, scene);
}
