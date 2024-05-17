/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:52:33 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/17 13:08:29 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// opening door state: g -> f -> e -> d -> c -> b -> a -> O = open
// closing door state: 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> D = closed

void	update_opening_door_state(t_game *game, int x, int y)
{
	game->door_opening = 1;
	if (game->map[y][x] == 'a')
	{
		game->map[y][x] = 'O';
		game->door_opening = 0;
	}
	else if (game->map[y][x] == 'b')
		game->map[y][x] = 'a';
	else if (game->map[y][x] == 'c')
		game->map[y][x] = 'b';
	else if (game->map[y][x] == 'd')
		game->map[y][x] = 'c';
	else if (game->map[y][x] == 'e')
		game->map[y][x] = 'd';
	else if (game->map[y][x] == 'f')
		game->map[y][x] = 'e';
	else if (game->map[y][x] == 'g')
		game->map[y][x] = 'f';
}

void	update_closing_door_state(t_game *game, int x, int y)
{
	game->door_closing = 1;
	if (game->map[y][x] == '8')
	{
		game->map[y][x] = 'D';
		game->door_closing = 0;
	}
	else if (game->map[y][x] == '7')
		game->map[y][x] = '8';
	else if (game->map[y][x] == '6')
		game->map[y][x] = '7';
	else if (game->map[y][x] == '5')
		game->map[y][x] = '6';
	else if (game->map[y][x] == '4')
		game->map[y][x] = '5';
	else if (game->map[y][x] == '3')
		game->map[y][x] = '4';
	else if (game->map[y][x] == '2')
		game->map[y][x] = '3';
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
			// printf("map[%d][%d] = %c\n", y, x, game->map[y][x]);
			if (game->map[y][x] && ft_strchr("abcdefg", game->map[y][x]))
			{
				update_opening_door_state(game, x, y);
				printf("%c\n", game->map[y][x]);
			}
			else if (game->map[y][x] && ft_strchr("2345678", game->map[y][x]))
			{
				update_closing_door_state(game, x, y);
				printf("%c\n", game->map[y][x]);
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
		if (game->map[y][x] == 'D')
		{
			game->map[y][x] = 'g';
			game->door_opening = 1;
		}
		else if (game->map[y][x] == 'O')
		{
			game->map[y][x] = '2';
			game->door_closing = 1;
		}
	}
}
