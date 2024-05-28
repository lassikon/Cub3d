/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:41:22 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/28 11:56:53 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
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
		}
	}
}

void	find_enemies(t_game *game)
{
	int		i;
	int		j;
	int		k;

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
				k++;
				if (k > 99)
					error_handler(NULL, ENEMIES_ERR);
			}
			j++;
		}
		i++;
	}
	game->enemy_count = k;
}

void	init_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		game->e[i].alive = false;
		game->e[i].dying = 0;
		game->e[i].rendered = false;
		game->e[i].attacking = 0;
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
	game->gun.aim_frme = -1;
	game->gun.fire_frme = -1;
	game->p.jumping = 0;
	game->p.hp = 100;
	find_player(game);
	init_enemies(game);
	init_textures(game, scene);
	init_math_tables(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
	game->map_width = scene->map_width * TILE;
	game->map_height = scene->map_height * TILE;
	mlx_image_to_window(game->mlx, game->mini_img, SCREEN_WIDTH - MINIMAP_SIZE, 0);
	mlx_set_instance_depth(&game->image->instances[0], 0);
	mlx_set_instance_depth(&game->mini_img->instances[0], 1);
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	init_jump_height_table(game);
}
