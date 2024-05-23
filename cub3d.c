/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:56:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/23 16:36:45 by lkonttin         ###   ########.fr       */
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
}

void	game_loop(void *param)
{
	t_game	*game;
	int		i;

	i = 0;
	game = (t_game *)param;
	init_frame(game);
	ft_memset(game->image->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	move_player(game);
	render_walls(game);
	while (i < game->enemy_count)
	{
		next_enemy_to_render(game);
		render_enemy(game, game->next_enemy_to_render, ((int)game->frame_count % 8) / 2);
		game->e[game->next_enemy_to_render].rendered = true;
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
