/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:56:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/29 11:43:07 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_frame(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		game->e[i].rendered = false;
		i++;
	}
	game->in_crosshairs_id = -1;
	ft_memset(game->image->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
}

void	render_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		next_enemy_to_render(game);
		if (game->next_enemy_to_render != -1)
		{
			render_enemy(game, game->next_enemy_to_render, \
			((int)game->frame_count % 16));
			game->e[game->next_enemy_to_render].rendered = true;
		}
		i++;
	}
}

int	all_enemies_dead(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->e[i].alive)
			return (0);
		i++;
	}
	return (1);
}

void	game_over(t_game *game)
{
	if (game->keep_playing)
		return ;
	if (game->p.hp == 0)
	{
		game->over = true;
		game->game_over_img->instances[0].enabled = true;
	}
	else if (!game->keep_playing && all_enemies_dead(game))
	{
		game->victory = true;
		game->win_img->instances[0].enabled = true;
	}
	if (game->victory && mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
	{
		game->keep_playing = true;
		game->victory = false;
		game->win_img->instances[0].enabled = false;
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	init_frame(game);
	game_over(game);
	move_player(game);
	render_walls(game);
	render_enemies(game);
	hitpoints(game, game->frame_count);
	moving_door(game);
	minimap(game);
	move_mouse(game);
	move_enemies(game);
	weapons(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	game->frame_count++;
	if (game->p.regen_cooldown > 0)
	game->p.regen_cooldown--;
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
