/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:23:34 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/05 16:50:07 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->p.x + cos(game->p.angle) * MOVE_SPEED;
	new_y = game->p.y + sin(game->p.angle) * MOVE_SPEED;
	if (wall_collision(game->map, (int)new_x, (int)new_y) == 0)
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_backward(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->p.x - cos(game->p.angle) * MOVE_SPEED;
	new_y = game->p.y - sin(game->p.angle) * MOVE_SPEED;
	if (wall_collision(game->map, (int)new_x, (int)new_y) == 0)
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_left(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->p.x + cos(game->p.angle - PI / 2) * MOVE_SPEED;
	new_y = game->p.y + sin(game->p.angle - PI / 2) * MOVE_SPEED;
	if (wall_collision(game->map, (int)new_x, (int)new_y) == 0)
	{
		game->p.x = new_x;
		game->p.y = new_y;
	}
}

void	move_right(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->p.x + cos(game->p.angle + PI / 2) * MOVE_SPEED;
	new_y = game->p.y + sin(game->p.angle + PI / 2) * MOVE_SPEED;
	if (wall_collision(game->map, (int)new_x, (int)new_y) == 0)
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
			game->p.angle += 2 * PI;
		//printf("L angle: %f\n", game->p.angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->p.angle += ROTATION_SPEED;
		if (game->p.angle > 2 * PI)
			game->p.angle -= 2 * PI;
		//printf("R angle: %f\n", game->p.angle);
	}
}
