/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:23:34 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/20 10:35:51 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_x_collision(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (ft_strchr(COL_CHARS, game->map[y / TILE][(x + COLL_OFFSET) / TILE]))
		return (1);
	if (ft_strchr(COL_CHARS, game->map[y / TILE][(x - COLL_OFFSET) / TILE]))
		return (1);
	if (ft_strchr(COL_CHARS, game->map[(y + COLL_OFFSET) / TILE][(x + COLL_OFFSET) / TILE]))
		return (1);
	if (ft_strchr(COL_CHARS, game->map[(y - COLL_OFFSET) / TILE][(x - COLL_OFFSET) / TILE]))
		return (1);
	return (0);
}

int	player_y_collision(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (ft_strchr(COL_CHARS, game->map[(y + COLL_OFFSET) / TILE][x / TILE]))
		return (1);
	if (ft_strchr(COL_CHARS, game->map[(y - COLL_OFFSET) / TILE][x / TILE]))
		return (1);
	if (ft_strchr(COL_CHARS, game->map[(y + COLL_OFFSET) / TILE][(x + COLL_OFFSET) / TILE]))
		return (1);
	if (ft_strchr(COL_CHARS, game->map[(y - COLL_OFFSET) / TILE][(x - COLL_OFFSET) / TILE]))
		return (1);
	return (0);
}

void	move_forward(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->p.x + cos(game->p.angle) * MOVE_SPEED;
	new_y = game->p.y + sin(game->p.angle) * MOVE_SPEED;
	if (!player_x_collision(game, (int)new_x, (int)game->p.y))
		game->p.x = new_x;
	if (!player_y_collision(game, (int)game->p.x, (int)new_y))
		game->p.y = new_y;
}

void	move_backward(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->p.x - cos(game->p.angle) * MOVE_SPEED;
	new_y = game->p.y - sin(game->p.angle) * MOVE_SPEED;
	if (!player_x_collision(game, (int)new_x, (int)game->p.y))
		game->p.x = new_x;
	if (!player_y_collision(game, (int)game->p.x, (int)new_y))
		game->p.y = new_y;
}

void	move_left(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->p.x + cos(game->p.angle - PI / 2) * MOVE_SPEED;
	new_y = game->p.y + sin(game->p.angle - PI / 2) * MOVE_SPEED;
	if (!player_x_collision(game, (int)new_x, (int)game->p.y))
		game->p.x = new_x;
	if (!player_y_collision(game, (int)game->p.x, (int)new_y))
		game->p.y = new_y;
}

void	move_right(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->p.x + cos(game->p.angle + PI / 2) * MOVE_SPEED;
	new_y = game->p.y + sin(game->p.angle + PI / 2) * MOVE_SPEED;
	if (!player_x_collision(game, (int)new_x, (int)game->p.y))
		game->p.x = new_x;
	if (!player_y_collision(game, (int)game->p.x, (int)new_y))
		game->p.y = new_y;
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
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->p.angle += ROTATION_SPEED;
		if (game->p.angle > 2 * PI)
			game->p.angle -= 2 * PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP) && game->vertical_center < SCREEN_HEIGHT - 20)
		game->vertical_center += 20;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN) && game->vertical_center > 20)
		game->vertical_center -= 20;
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE) && game->p.height < WALL_HEIGHT)
	{
		game->p.height += 1;
		if (game->p.height > WALL_HEIGHT - 1)
			game->p.height = WALL_HEIGHT - 1;
		//printf("game->p.height++: %d\n", game->p.height);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL) && game->p.height > 0)
	{
		game->p.height -= 1;
		if (game->p.height < 1)
			game->p.height = 1;
		//printf("game->p.height--: %d\n", game->p.height);
	}
}
