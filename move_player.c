/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:23:34 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/02 16:28:45 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	int		new_x;
	int		new_y;

	new_x = game->p.x + cos(game->p.angle) * MOVEMENT_SPEED;
	new_y = game->p.y + sin(game->p.angle) * MOVEMENT_SPEED;
	if (game->map[new_y / TILE_SIZE][new_x / TILE_SIZE] == 0)
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_backward(t_game *game)
{
	int		new_x;
	int		new_y;

	new_x = game->p.x - cos(game->p.angle) * MOVEMENT_SPEED;
	new_y = game->p.y - sin(game->p.angle) * MOVEMENT_SPEED;
	if (game->map[new_y / TILE_SIZE][new_x / TILE_SIZE] == 0)
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_left(t_game *game)
{
	int		new_x;
	int		new_y;

	new_x = game->p.x - cos(game->p.angle + M_PI / 2) * STRAFE_SPEED;
	new_y = game->p.y - sin(game->p.angle + M_PI / 2) * STRAFE_SPEED;
	if (game->map[new_y / TILE_SIZE][new_x / TILE_SIZE] == 0)
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_right(t_game *game)
{
	int		new_x;
	int		new_y;

	new_x = game->p.x + cos(game->p.angle + M_PI / 2) * STRAFE_SPEED;
	new_y = game->p.y + sin(game->p.angle + M_PI / 2) * STRAFE_SPEED;
	if (game->map[new_y / TILE_SIZE][new_x / TILE_SIZE] == 0)
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->p.angle -= ROTATION_SPEED;
		if (game->p.angle < 0)
			game->p.angle += 2 * M_PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->p.angle += ROTATION_SPEED;
		if (game->p.angle > 2 * M_PI)
			game->p.angle -= 2 * M_PI;
	}
}
