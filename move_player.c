/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:23:34 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/23 09:40:25 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_x_collision(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (ft_strchr(C_CHARS, game->map[(y - C_BUF) / TILE][(x + C_BUF) / TILE]))
		return (1);
	if (ft_strchr(C_CHARS, game->map[(y - C_BUF) / TILE][(x - C_BUF) / TILE]))
		return (1);
	if (ft_strchr(C_CHARS, game->map[(y + C_BUF) / TILE][(x + C_BUF) / TILE]))
		return (1);
	if (ft_strchr(C_CHARS, game->map[(y + C_BUF) / TILE][(x - C_BUF) / TILE]))
		return (1);
	return (0);
}

int	player_y_collision(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (ft_strchr(C_CHARS, game->map[(y - C_BUF) / TILE][(x + C_BUF) / TILE]))
		return (1);
	if (ft_strchr(C_CHARS, game->map[(y - C_BUF) / TILE][(x - C_BUF) / TILE]))
		return (1);
	if (ft_strchr(C_CHARS, game->map[(y + C_BUF) / TILE][(x + C_BUF) / TILE]))
		return (1);
	if (ft_strchr(C_CHARS, game->map[(y + C_BUF) / TILE][(x - C_BUF) / TILE]))
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
	move_player_vertical(game);
}

void	move_enemy_single(t_game *game, t_enemy *e)
{
	if (e->x < 0 || e->x >= game->map_width || e->y < 0 || e->y >= game->map_height)
		return;
	if (e->x > game->p.x)
		if (!player_x_collision(game, (int)e->x - ENEMY_SPEED, (int)e->y))
			e->x -= ENEMY_SPEED;
	if (e->x < game->p.x)
		if (!player_x_collision(game, (int)e->x + ENEMY_SPEED, (int)e->y))
			e->x += ENEMY_SPEED;
	if (e->y > game->p.y)
		if (!player_y_collision(game, (int)e->x, (int)e->y - ENEMY_SPEED ))
			e->y -= ENEMY_SPEED;
	if (e->y < game->p.y)
		if (!player_y_collision(game, (int)e->x, (int)e->y + ENEMY_SPEED))
			e->y += ENEMY_SPEED;
}

void	move_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		move_enemy_single(game, &game->e[i]);
		i++;
	}
}
