/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:06:50 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/21 14:13:04 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_orientation(t_game *game, char c)
{
	if (c == 'N')
		game->p.angle = 3 * PI / 2;
	if (c == 'S')
		game->p.angle = PI / 2;
	if (c == 'W')
		game->p.angle = PI;
	if (c == 'E')
		game->p.angle = 0;
}

void	player_starting_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (ft_strchr("NSWE", game->map[i][j]) != NULL)
			{
				player_orientation(game, game->map[i][j]);
				game->p.x = j * TILE + TILE / 2;
				game->p.y = i * TILE + TILE / 2;
			}
			j++;
		}
		i++;
	}
}

void	resize_images(t_game *game)
{
	if (mlx_resize_image(game->north_img, 512, 512) == false)
		mlx_error_exit(game, NULL);
	if (mlx_resize_image(game->south_img, 512, 512) == false)
		mlx_error_exit(game, NULL);
	if (mlx_resize_image(game->east_img, 512, 512) == false)
		mlx_error_exit(game, NULL);
	if (mlx_resize_image(game->west_img, 512, 512) == false)
		mlx_error_exit(game, NULL);
}

void	init_game(t_game *game, t_scene *scene)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		mlx_error_exit(game, scene);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->image)
		mlx_error_exit(game, scene);
	game->dist_to_proj_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	game->vertical_center = SCREEN_HEIGHT / 2;
	game->map = scene->map;
	player_starting_position(game);
	init_textures(game, scene);
	resize_images(game);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
		mlx_error_exit(game, scene);
	game->map_width = scene->map_width * TILE;
	game->map_height = scene->map_height * TILE;
	mlx_set_instance_depth(&game->image->instances[0], 0);
	game->ceiling_color = scene->ceiling_color;
	game->floor_color = scene->floor_color;
}
