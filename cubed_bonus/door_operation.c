/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:09:09 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/24 15:07:50 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_opening_door_state(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'm')
	{
		game->map[y][x] = '3';
	}
	else
		game->map[y][x] += 1;
}

static void	update_closing_door_state(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'n')
	{
		game->map[y][x] = '2';
	}
	else
		game->map[y][x] -= 1;
}

void	update_door_state(t_game *game)
{
	int			x;
	int			y;
	static int	delay;

	if (delay < DOOR_SPEED)
	{
		delay++;
		return ;
	}
	y = 0;
	while (y < game->map_height / TILE)
	{
		x = 0;
		while (x < game->map_width / TILE)
		{
			if (game->map[y][x] && ft_strchr("abcdefghijklm", game->map[y][x]))
				update_opening_door_state(game, x, y);
			else if (game->map[y][x]
				&& ft_strchr("nopqrstuvwxyz", game->map[y][x]))
				update_closing_door_state(game, x, y);
			x++;
		}
		y++;
	}
	delay = 0;
}

int	player_too_close(t_game *game, int x, int y)
{
	if (game->p.x > x * TILE - C_BUF
		&& game->p.x < x * TILE + TILE + C_BUF)
	{
		if (game->p.y > y * TILE - C_BUF
			&& game->p.y < y * TILE + TILE + C_BUF)
			return (1);
	}
	return (0);
}

void	operate_door(mlx_key_data_t data, void *param)
{
	int		x;
	int		y;
	t_game	*game;

	game = (t_game *)param;
	if (data.key == MLX_KEY_E && data.action == MLX_PRESS)
	{
		x = (int)(game->p.x + cos(game->p.angle) * TILE) / TILE;
		y = (int)(game->p.y + sin(game->p.angle) * TILE) / TILE;
		if (game->map[y][x] == '2')
		{
			game->map[y][x] = 'a';
		}
		else if (game->map[y][x] == '3')
		{
			if (player_too_close(game, x, y))
				return ;
			game->map[y][x] = 'z';
		}
	}
}
