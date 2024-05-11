/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:56:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/10 19:59:04 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_char(t_game *game)
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
				if (game->map[i][j] == 'N')
					game->p.angle = 3 * PI / 2;
				if (game->map[i][j] == 'S')
					game->p.angle = PI / 2;
				if (game->map[i][j] == 'W')
					game->p.angle = PI;
				if (game->map[i][j] == 'E')
					game->p.angle = 0;
				game->p.x = j * TILE_SIZE + TILE_SIZE / 2;
				game->p.y = i * TILE_SIZE + TILE_SIZE / 2;
			}
			j++;
		}
		i++;
	}
}

void	init_textures(t_game *game, t_scene *scene)
{
	scene->north_tex = mlx_load_png(scene->no_texture);
	scene->south_tex = mlx_load_png(scene->so_texture);
	scene->east_tex = mlx_load_png(scene->ea_texture);
	scene->west_tex = mlx_load_png(scene->we_texture);
	scene->door_tex = mlx_load_png("textures/stone_wall.png");
	game->north_img = mlx_texture_to_image(game->mlx, scene->north_tex);
	game->south_img = mlx_texture_to_image(game->mlx, scene->south_tex);
	game->east_img = mlx_texture_to_image(game->mlx, scene->east_tex);
	game->west_img = mlx_texture_to_image(game->mlx, scene->west_tex);
	game->door_img = mlx_texture_to_image(game->mlx, scene->door_tex);
}

void	init_game(t_game *game, t_scene *scene)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mini_img = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	game->dist_to_proj_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	game->p.height = 32;
	game->vertical_center = SCREEN_HEIGHT / 2;
	game->map = scene->map;
	find_char(game);
	// game->no_txtr = mlx_load_png("textures/blacknwhite.png");
	// game->no_txtr = mlx_load_png("textures/checker.png");
	// game->no_txtr = mlx_load_png("textures/tile_wall.png");
	// game->no_img = mlx_texture_to_image(game->mlx, game->no_txtr);
	init_textures(game, scene);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
	game->map_width = scene->map_width * TILE_SIZE;
	game->map_height = scene->map_height * TILE_SIZE;
	mlx_image_to_window(game->mlx, game->mini_img, SCREEN_WIDTH - MINIMAP_SIZE, 0);
	mlx_set_instance_depth(&game->image->instances[0], 0);
	mlx_set_instance_depth(&game->mini_img->instances[0], 1);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_memset(game->image->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	move_player(game);
	render_walls(game);
	minimap(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	game->frame_count++;
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_scene	scene;

	parse(&scene, argc, argv);
	init_game(&game, &scene);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	printf("Average FPS: %f\n", game.frame_count / mlx_get_time());
	mlx_terminate(game.mlx);
	free_scene(&scene);
	return (0);
}
