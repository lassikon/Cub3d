/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:09:09 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/17 16:09:30 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_opening_door_state(t_game *game, int x, int y)
{
	game->door_opening = 1;
	if (game->map[y][x] == 'm')
	{
		game->map[y][x] = '3';
		game->door_opening = 0;
	}
	else
		game->map[y][x] += 1;
}

void	update_closing_door_state(t_game *game, int x, int y)
{
	game->door_closing = 1;
	if (game->map[y][x] == 'n')
	{
		game->map[y][x] = '2';
		game->door_closing = 0;
	}
	else
		game->map[y][x] -= 1;
}

void	animate_door(t_game *game)
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
	while (y < game->map_height / TILE_SIZE)
	{
		x = 0;
		while (x < game->map_width / TILE_SIZE)
		{
			if (game->map[y][x] && ft_strchr("abcdefghijklm", game->map[y][x]))
			{
				printf("%c\n", game->map[y][x]);
				update_opening_door_state(game, x, y);
			}
			else if (game->map[y][x] && ft_strchr("nopqrstuvwxyz", game->map[y][x]))
			{
				printf("%c\n", game->map[y][x]);
				update_closing_door_state(game, x, y);
			}
			x++;
		}
		y++;
	}
	delay = 0;
}

int	player_too_close(t_game *game, int x, int y)
{
	if (game->p.x > x * TILE_SIZE - COLL_OFFSET
		&& game->p.x < x * TILE_SIZE + TILE_SIZE + COLL_OFFSET)
	{
		if (game->p.y > y * TILE_SIZE - COLL_OFFSET
			&& game->p.y < y * TILE_SIZE + TILE_SIZE + COLL_OFFSET)
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
		x = (int)(game->p.x + cos(game->p.angle) * TILE_SIZE) / TILE_SIZE;
		y = (int)(game->p.y + sin(game->p.angle) * TILE_SIZE) / TILE_SIZE;
		if (game->map[y][x] == '2')
		{
			game->map[y][x] = 'a';
			game->door_opening = 1;
		}
		else if (game->map[y][x] == '3')
		{
			game->map[y][x] = 'z';
			game->door_closing = 1;
		}
	}
}