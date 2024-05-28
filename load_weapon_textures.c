/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapon_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:04:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/28 11:11:53 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture_name(char *buffer, char *path, int i)
{
	char	itoa[100];

	ft_memset(buffer, 0, 100);
	ft_memset(itoa, 0, 100);
	ft_itoa_stack(itoa, i);
	ft_strlcpy(buffer, path, ft_strlen(path) + 1);
	ft_strlcat(buffer, itoa, ft_strlen(buffer) + ft_strlen(itoa) + 1);
	ft_strlcat(buffer, ".png", ft_strlen(buffer) + 5);
}

void	load_fire_images(t_game *game, t_scene *scene)
{
	int		i;
	char	buffer[100];

	i = 0;
	while (i < 14)
	{
		get_texture_name(buffer, "sprites/hk53/hk53_fire.", i);
		game->gun.hk53_fire_tx[i] = mlx_load_png(buffer);
		if (game->gun.hk53_fire_tx[i] == NULL)
			mlx_error_exit(game, scene);
		game->gun.hk53_fire_img[i] = mlx_texture_to_image(game->mlx, \
		game->gun.hk53_fire_tx[i]);
		mlx_resize_image(game->gun.hk53_fire_img[i], \
		SCREEN_WIDTH, SCREEN_HEIGHT);
		mlx_image_to_window(game->mlx, game->gun.hk53_fire_img[i], 0, 0);
		mlx_set_instance_depth(&game->gun.hk53_fire_img[i]->instances[0], \
		2);
		game->gun.hk53_fire_img[i]->enabled = false;
		i++;
	}
}

void	load_aim_images(t_game *game, t_scene *scene)
{
	int		i;
	char	buffer[100];

	i = 0;
	while (i < 12)
	{
		get_texture_name(buffer, "sprites/hk53/hk53_aim.", i + 1);
		game->gun.hk53_aim_mid_tx[i] = mlx_load_png(buffer);
		if (game->gun.hk53_aim_mid_tx[i] == NULL)
			mlx_error_exit(game, scene);
		game->gun.hk53_aim_mid_img[i] = mlx_texture_to_image(game->mlx, \
		game->gun.hk53_aim_mid_tx[i]);
		mlx_resize_image(game->gun.hk53_aim_mid_img[i], \
		SCREEN_WIDTH, SCREEN_HEIGHT);
		mlx_image_to_window(game->mlx, game->gun.hk53_aim_mid_img[i], 0, 0);
		mlx_set_instance_depth(&game->gun.hk53_aim_mid_img[i]->instances[0], \
		2);
		game->gun.hk53_aim_mid_img[i]->enabled = false;
		i++;
	}
}

void	load_mid_fire_images(t_game *game, t_scene *scene)
{
	int		i;
	char	buffer[100];

	i = 0;
	while (i < 13)
	{
		get_texture_name(buffer, "sprites/hk53/hk53_aimfire.", i + 1);
		game->gun.hk53_fire_mid_tx[i] = mlx_load_png(buffer);
		if (game->gun.hk53_fire_mid_tx[i] == NULL)
			mlx_error_exit(game, scene);
		game->gun.hk53_fire_mid_img[i] = mlx_texture_to_image(game->mlx, \
		game->gun.hk53_fire_mid_tx[i]);
		mlx_resize_image(game->gun.hk53_fire_mid_img[i], \
		SCREEN_WIDTH, SCREEN_HEIGHT);
		mlx_image_to_window(game->mlx, game->gun.hk53_fire_mid_img[i], 0, 0);
		mlx_set_instance_depth(&game->gun.hk53_fire_mid_img[i]->instances[0], \
		2);
		game->gun.hk53_fire_mid_img[i]->enabled = false;
		i++;
	}
}

void	load_weapon_textures(t_game *game, t_scene *scene)
{
	load_fire_images(game, scene);
	load_aim_images(game, scene);
	load_mid_fire_images(game, scene);
}
