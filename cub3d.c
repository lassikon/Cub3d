/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:56:13 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/01 19:52:14 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
};

void	init_game(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->p.x = TILE_SIZE * 1.5f;
	game->p.y = TILE_SIZE * 1.5f;
	game->p.angle = 0.0f;
	ft_memcpy(game->map, map, sizeof(map));
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}

void	game_loop(void *param)
{
	t_game *game = (t_game *)param;

	ft_memset(game->image->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	move_player(game);
	render_walls(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}