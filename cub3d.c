/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:56:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/05 12:57:57 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "cub3d.h"

/* void	minimap(t_game *game)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		color;

	x = 0;
	while (x < MINIMAP_SIZE)
	{
		y = 0;
		while (y < MINIMAP_SIZE)
		{
			i = x * MAP_WIDTH / MINIMAP_SIZE;
			j = y * MAP_HEIGHT / MINIMAP_SIZE;
			if (game->p.x / TILE_SIZE == i && game->p.y / TILE_SIZE == j)
				color = 0x00FF0000;
			else if (game->map[j][i] == '1')
				color = 0x00FF00FF;
			else
				color = 0x00000000;
			mlx_put_pixel(game->minimap, x, y, color);
			y++;
		}
		x++;
	}
} */

void	init_game(t_game *game, t_scene *scene)
{
	//char	*map;

	//map = "11111111\n10000001\n10001001\n10000001\n10000001\n10000001\n10000001\n11111111";
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// game->minimap = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	game->distance_to_projection_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	game->p.x = 2 * TILE_SIZE + TILE_SIZE / 2;
	game->p.y = 2 * TILE_SIZE + TILE_SIZE / 2;
	game->p.angle = 0.0f;
	// game->p.angle = M_PI / 2;
	//game->map = ft_split(map, '\n');
	game->map = scene->map;
	print_array(game->map);
	print_array(scene->map);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
	// mlx_image_to_window(game->mlx, game->minimap, SCREEN_WIDTH - MINIMAP_SIZE, 0);
	// mlx_set_instance_depth(game->minimap->instances, 1);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_memset(game->image->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	move_player(game);
	render_walls(game);
	// minimap(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_scene	scene;

	parse(&scene, argc, argv);
	init_game(&game, &scene);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free(game.map);

	return (0);
}
