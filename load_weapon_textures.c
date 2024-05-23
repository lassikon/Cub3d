/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapon_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:04:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/23 16:07:45 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture_name(t_game *game, char *buffer, char *path, int i)
{
	char	*frame;

	(void)game;
	ft_memset(buffer, 0, 100);
	frame = ft_itoa(i);
	if (!frame)
		exit(1);
	ft_strlcpy(buffer, path, ft_strlen(path) + 1);
	ft_strlcat(buffer, frame, ft_strlen(buffer) + ft_strlen(frame) + 1);
	ft_strlcat(buffer, ".png", ft_strlen(buffer) + 5);
}

void	init_sprites(t_game *game)
{
	int		i;
	char	buffer[100];

	i = 0;
	/*fire*/
	while (i < 14)
	{
		get_texture_name(game, buffer, "sprites/hk53/hk53_fire.", i);
		game->sprite.hk53_fire_tx[i] = mlx_load_png(buffer);
		game->sprite.hk53_fire_img[i] = mlx_texture_to_image(game->mlx, game->sprite.hk53_fire_tx[i]);
		mlx_resize_image(game->sprite.hk53_fire_img[i], SCREEN_WIDTH, SCREEN_HEIGHT);
		i++;
	}
	i = 0;
	while (i < 14)
	{
		mlx_image_to_window(game->mlx, game->sprite.hk53_fire_img[i], 0, 0);
		mlx_set_instance_depth(&game->sprite.hk53_fire_img[i]->instances[0], 2 + i);
		game->sprite.hk53_fire_img[i]->enabled = false;
		i++;
	}

	/*aim mid*/
	i = 0;
	while (i < 12)
	{
		get_texture_name(game, buffer, "sprites/hk53/hk53_aim.", i + 1);
		game->sprite.hk53_aim_mid_tx[i] = mlx_load_png(buffer);
		game->sprite.hk53_aim_mid_img[i] = mlx_texture_to_image(game->mlx, game->sprite.hk53_aim_mid_tx[i]);
		mlx_resize_image(game->sprite.hk53_aim_mid_img[i], SCREEN_WIDTH, SCREEN_HEIGHT);
		i++;
	}
	i = 0;
	while (i < 12)
	{
		mlx_image_to_window(game->mlx, game->sprite.hk53_aim_mid_img[i], 0, 0);
		mlx_set_instance_depth(&game->sprite.hk53_aim_mid_img[i]->instances[0], 3 + i);
		game->sprite.hk53_aim_mid_img[i]->enabled = false;
		i++;
	}
	/*mid fire*/
	i = 0;
	while (i < 13)
	{
		get_texture_name(game, buffer, "sprites/hk53/hk53_aimfire.", i + 1);
		game->sprite.hk53_fire_mid_tx[i] = mlx_load_png(buffer);
		game->sprite.hk53_fire_mid_img[i] = mlx_texture_to_image(game->mlx, game->sprite.hk53_fire_mid_tx[i]);
		mlx_resize_image(game->sprite.hk53_fire_mid_img[i], SCREEN_WIDTH, SCREEN_HEIGHT);
		i++;
	}
	i = 0;
	while (i < 13)
	{
		mlx_image_to_window(game->mlx, game->sprite.hk53_fire_mid_img[i], 0, 0);
		mlx_set_instance_depth(&game->sprite.hk53_fire_mid_img[i]->instances[0], 3 + i);
		game->sprite.hk53_fire_mid_img[i]->enabled = false;
		i++;
	}
}

void	load_weapon_textures(t_game *game)
{
	init_sprites(game);
}
