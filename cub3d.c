/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:56:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/16 20:16:50 by janraub          ###   ########.fr       */
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
	game->north_img = mlx_texture_to_image(game->mlx, scene->north_tex);
	game->south_img = mlx_texture_to_image(game->mlx, scene->south_tex);
	game->east_img = mlx_texture_to_image(game->mlx, scene->east_tex);
	game->west_img = mlx_texture_to_image(game->mlx, scene->west_tex);
	game->door_img = NULL;
	game->floor_img = NULL;
	game->ceiling_img = NULL;
	if (scene->dr_texture)
	{
		scene->door_tex = mlx_load_png(scene->dr_texture);
		game->door_img = mlx_texture_to_image(game->mlx, scene->door_tex);
	}
	if (scene->fl_texture)
	{
		scene->floor_tex = mlx_load_png(scene->fl_texture);
		game->floor_img = mlx_texture_to_image(game->mlx, scene->floor_tex);
	}
	if (scene->cl_texture)
	{
		scene->ceiling_tex = mlx_load_png(scene->cl_texture);
		game->ceiling_img = mlx_texture_to_image(game->mlx, scene->ceiling_tex);
	}
}

void	fill_math_table(t_game *game)
{
	float	angle;
	int		i;

	i = 0;
	angle = 0;
	while (i < SCREEN_WIDTH * 6)
	{
		game->math.sin[i] = sinf(angle) + .0001;
		game->math.cos[i] = cosf(angle) + .0001;
		game->math.tan[i] = tanf(angle) + .0001;
		game->math.isin[i] = 1 / game->math.sin[i];
		game->math.icos[i] = 1 / game->math.cos[i];
		game->math.itan[i] = 1 / game->math.tan[i];
		angle += game->angle_step;
		i++;
	}
}

void	init_math_tables(t_game *game)
{
	float	angle;
	float	fish_step;
	int		i;

	ft_bzero(game->math.sin, SCREEN_WIDTH * sizeof(float) * 6);
	ft_bzero(game->math.cos, SCREEN_WIDTH * sizeof(float) * 6);
	ft_bzero(game->math.tan, SCREEN_WIDTH * sizeof(float) * 6);
	ft_bzero(game->math.isin, SCREEN_WIDTH * sizeof(float) * 6);
	ft_bzero(game->math.icos, SCREEN_WIDTH * sizeof(float) * 6);
	ft_bzero(game->math.itan, SCREEN_WIDTH * sizeof(float) * 6);
	ft_bzero(game->math.fishcos, 360 * sizeof(float));
	ft_bzero(game->math.ifishcos, 360 * sizeof(float));
	fill_math_table(game);
	i = 0;
	fish_step = FOV / 60;
	angle = 0;
	while (i < 360)
	{
		game->math.fishcos[i] = cos(angle) + .0001;
		game->math.ifishcos[i] = 1 / game->math.fishcos[i];
		angle += fish_step;
		i++;
	}
	game->math.trig_it = 1 / game->angle_step;
	game->math.fish_it = 1 / fish_step;
}

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

void	init_game(t_game *game, t_scene *scene)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mini_img = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	game->dist_to_proj_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	game->p.height = 32;
	game->vertical_center = SCREEN_HEIGHT / 2;
	game->angle_step = FOV / SCREEN_WIDTH;
	game->map = scene->map;
	game->floor_color = scene->floor_color;
	game->ceiling_color = scene->ceiling_color;
	game->sprite.weapon_aim = -1;
	game->sprite.weapon_fire = -1;
	find_char(game);
	init_textures(game, scene);
	init_sprites(game);
	init_math_tables(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
	game->map_width = scene->map_width * TILE_SIZE;
	game->map_height = scene->map_height * TILE_SIZE;
	mlx_image_to_window(game->mlx, game->mini_img, SCREEN_WIDTH - MINIMAP_SIZE, 0);
	mlx_set_instance_depth(&game->image->instances[0], 0);
	mlx_set_instance_depth(&game->mini_img->instances[0], 1);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
}

int	player_too_close(t_game *game, int x, int y)
{
	if (game->p.x > x * TILE_SIZE - COLL_OFFSET
		&& game->p.x < x * TILE_SIZE + TILE_SIZE + COLL_OFFSET)
	{
		if (game->p.y > y * TILE_SIZE - COLL_OFFSET
			&& game->p.y < y * TILE_SIZE + TILE_SIZE + COLL_OFFSET)
			return (1);
	}
	return (0);
}

void	operate_door(mlx_key_data_t data, void *param)
{
	int	x;
	int	y;
	t_game	*game;

	game = (t_game *)param;
	if (data.key == MLX_KEY_E && data.action == MLX_PRESS)
	{
		x = (int)(game->p.x + cos(game->p.angle) * TILE_SIZE) / TILE_SIZE;
		y = (int)(game->p.y + sin(game->p.angle) * TILE_SIZE) / TILE_SIZE;
		if (game->map[y][x] == 'D')
			game->map[y][x] = 'O';
		else if (game->map[y][x] == 'O')
		{
			if (!player_too_close(game, x, y))
				game->map[y][x] = 'D';
		}
	}
}


void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_memset(game->image->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	move_player(game);
	render_walls(game);
	minimap(game);
	move_mouse(game);
	weapons(game);
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
	mlx_key_hook(game.mlx, operate_door, &game);
	mlx_loop(game.mlx);
	printf("Average FPS: %f\n", game.frame_count / mlx_get_time());
	mlx_terminate(game.mlx);
	free_scene(&scene);
	return (0);
}
