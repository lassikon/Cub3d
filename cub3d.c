/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:56:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/08 15:29:32 by lkonttin         ###   ########.fr       */
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

/*segfaults on 7row below by 8col*/
void	init_game(t_game *game, t_scene *scene)
{
	//char	*map;

	//map = "11111111\n10000001\n10001001\n10000001\n10000001\n10000001\n10000001\n11111111";
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mini_img = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	game->distance_to_projection_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	/* game->p.x = 6 * TILE_SIZE + TILE_SIZE / 2;
	game->p.y = 6 * TILE_SIZE + TILE_SIZE / 2;
	game->p.angle = 0.0f; */
	// game->p.angle = M_PI / 2;
	//game->map = ft_split(map, '\n');

	game->map = scene->map;
	find_char(game);
	// game->no_txtr = mlx_load_png("textures/blacknwhite.png");
	game->no_txtr = mlx_load_png("textures/checker.png");
	// game->no_txtr = mlx_load_png("textures/wall.png");
	game->no_img = mlx_texture_to_image(game->mlx, game->no_txtr);
	printf("image width: %d\n", game->no_img->width);
	printf("image height: %d\n", game->no_img->height);
	// mlx_resize_image(game->no_img, 512, 512);
	mlx_image_to_window(game->mlx, game->image, 0, 0);

	// uint32_t nwidth = 60;
	// uint32_t nheight = 321;

	// uint32_t* origin = (uint32_t*)game->no_img->pixels;
	// float wstep = (float)game->no_img->width / nwidth;
	// float hstep = (float)game->no_img->height / nheight;

	// uint8_t* tempbuff = calloc(nwidth * nheight, 4);
	
	// game->no_img->pixels = tempbuff;

	// uint32_t* destin = (uint32_t*)game->no_img->pixels;
	// for (uint32_t j = 0; j < nheight; j++)
	// 	for (uint32_t i = 0; i < nwidth; i++)
	// 		destin[j * nwidth + i] = origin[(uint32_t)(j * hstep) * game->no_img->width + (uint32_t)(i * wstep)];
	// (*(uint32_t*)&game->no_img->width) = nwidth;
	// (*(uint32_t*)&game->no_img->height) = nheight;


    // for (uint32_t y = 0; y < (uint32_t)game->no_img->height; y++)
    // {
    // 	for (uint32_t x = 0; x < (uint32_t)game->no_img->width; x++)
    //     {
    //         uint8_t* pixelstart = &game->no_img->pixels[(uint32_t)(y  * game->no_img->width + x) * 4];
    //         uint8_t red = pixelstart[0];     // Red component
    //         uint8_t green = pixelstart[1];   // Green component
    //         uint8_t blue = pixelstart[2];    // Blue component
    //         uint8_t alpha = pixelstart[3];
    //         int color = get_rgba(red, green, blue, alpha);
    //         mlx_put_pixel(game->image, x, y, color);
    //     }
    // }
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
