/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:56:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/22 13:55:17 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	find_player(t_game *game)
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
				game->p.x = j * TILE + TILE / 2;
				game->p.y = i * TILE + TILE / 2;
			}
			j++;
		}
		i++;
	}
}

void	find_enemies(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if ((game->map[i][j]) == '*')
			{
				game->e[k].x = j * TILE + TILE / 2;
				game->e[k].y = i * TILE + TILE / 2;
				game->e[k].alive = true;
				game->e[k].tx = mlx_load_png("textures/hero.png");
				game->e[k].img = mlx_texture_to_image(game->mlx, game->e[k].tx);
				mlx_resize_image(game->e[k].img, 512, 512);
				k++;
				if (k > 99)
					break ;
			}
			j++;
		}
		i++;
	}
	game->enemy_count = k;
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

void	init_jump_height_table(t_game *game)
{
	int		i;
	int		speed;
	int		height;

	speed = 6;
	height = TILE / 2;
	i = 0;
	while (i < 13)
	{
		game->p.jump_height[i] = (int)height;
		height += speed;
		speed -= 1;
		i++;
	}
	game->p.jump_height[13] = TILE / 2;
}

void	init_enemies(t_game *game)
{
	int i;

	i = 0;
	while (i < 100)
	{
		game->e[i].alive = false;
		i++;
	}
	find_enemies(game);
}

void	init_game(t_game *game, t_scene *scene)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mini_img = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	game->dist_to_proj_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	game->p.height = TILE / 2;
	game->vertical_center = SCREEN_HEIGHT / 2;
	game->angle_step = FOV / SCREEN_WIDTH;
	game->map = scene->map;
	game->floor_color = scene->floor_color;
	game->ceiling_color = scene->ceiling_color;
	game->sprite.weapon_aim = -1;
	game->sprite.weapon_fire = -1;
	game->p.jumping = 0;
	find_player(game);
	init_textures(game, scene);
	init_sprites(game);
	init_math_tables(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
	game->map_width = scene->map_width * TILE;
	game->map_height = scene->map_height * TILE;
	mlx_image_to_window(game->mlx, game->mini_img, SCREEN_WIDTH - MINIMAP_SIZE, 0);
	mlx_set_instance_depth(&game->image->instances[0], 0);
	mlx_set_instance_depth(&game->mini_img->instances[0], 1);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_resize_image(game->north_img, 512, 512);
	mlx_resize_image(game->south_img, 512, 512);
	mlx_resize_image(game->east_img, 512, 512);
	mlx_resize_image(game->west_img, 512, 512);
	if (game->door_img)
		mlx_resize_image(game->door_img, 512, 512);
	init_jump_height_table(game);
	init_enemies(game);
}

void	render_enemy(t_game *game, int i)
{
	if (game->e[i].alive == false)
		return ;
	float relative_x = game->e[i].x - game->p.x;
    float relative_y = game->e[i].y - game->p.y;
	float camera_x = relative_y * cosf(game->p.angle) - relative_x * sinf(game->p.angle);
    float camera_y = relative_y * sinf(game->p.angle) + relative_x * cosf(game->p.angle);
	float distance = sqrtf(camera_x * camera_x + camera_y * camera_y);
	if (camera_y <= 0)
		return;
	float ratio = game->dist_to_proj_plane / camera_y;
	int sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + (camera_x / camera_y)));
    int sprite_height = (int)((WALL_HEIGHT/ camera_y) * game->dist_to_proj_plane);
	float ty = 0;
	float ty_step = (float)game->e[i].img->height / sprite_height;
    int draw_end_y = (ratio * game->p.height) + game->vertical_center;
	int draw_start_y = draw_end_y - sprite_height;
    if (draw_start_y < 0)
	{
		ty += -draw_start_y * ty_step;
		draw_start_y = 0;
	}
    if (draw_end_y >= SCREEN_HEIGHT)
		draw_end_y = SCREEN_HEIGHT - 1;
	ty_step = fmod(ty_step, game->e[i].img->height);
	float tx_step = (float)game->e[i].img->width / sprite_height;
	float tx = 0;
    int draw_start_x = -sprite_height / 2 + sprite_screen_x;
    int draw_end_x = sprite_height / 2 + sprite_screen_x;
    if (draw_start_x < 0)
	{
		tx += -draw_start_x * tx_step;
		draw_start_x = 0;
	}
    if (draw_end_x >= SCREEN_WIDTH)
		draw_end_x = SCREEN_WIDTH - 1;
	tx_step = fmod(tx_step, game->e[i].img->width);
	float tx_tmp = tx;
	for (int y = draw_start_y; y < draw_end_y; y++)
	{
		tx = tx_tmp;
		for (int x = draw_start_x; x < draw_end_x; x++)
		{
			int	color;
			int	red;
			int	green;
			int	blue;
			int	alpha;

			uint8_t *pixel = &game->e[i].img->pixels[(int)ty * game->e[i].img->width * 4 + (int)tx * 4];
			red = pixel[0];
			green = pixel[1];
			blue = pixel[2];
			alpha = pixel[3];
			color = get_rgba(red, green, blue, alpha);
			if (alpha != 0 && (distance < game->rays[x].distance))
			{
				mlx_put_pixel(game->image, x, y, color);
			}
			tx += tx_step;
			if (tx >= game->e[i].img->width)
				break ;
		}
		ty += ty_step;
		if (ty >= game->e[i].img->height)
			break ;
	}
	if (SCREEN_WIDTH / 2 > draw_start_x && SCREEN_WIDTH / 2 < draw_end_x)
	{
		if (SCREEN_HEIGHT / 2 > draw_start_y && SCREEN_HEIGHT / 2 < draw_end_y)
		{
			game->rays[SCREEN_WIDTH / 2].enemy_top = draw_start_y;
			game->rays[SCREEN_WIDTH / 2].enemy_bottom = draw_end_y;
			printf("Aiming at enemy\n");
		}
		else
			printf("Aiming at enemy, but not in y range\n");
	}
	else
		printf("Not aiming at enemy\n");
}

void	game_loop(void *param)
{
	t_game	*game;
	int	i;

	i = 0;
	game = (t_game *)param;
	ft_memset(game->image->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	move_player(game);
	render_walls(game);
	while (i < game->enemy_count)
	{
		render_enemy(game, i);
		i++;
	}
	moving_door(game);
	animate_door(game);
	minimap(game);
	move_mouse(game);
	move_enemy(game);
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
