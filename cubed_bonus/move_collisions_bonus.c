/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_collisions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:55:44 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 11:07:03 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	player_to_enemy_collision(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->e[i].alive)
		{
			if (game->e[i].x > x - E_SIZE && game->e[i].x < x + E_SIZE
				&& game->e[i].y > y - E_SIZE && game->e[i].y < y + E_SIZE)
				return (1);
		}
		i++;
	}
	return (0);
}

int	move_collision(t_game *game, int x, int y)
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
	if (player_to_enemy_collision(game, x, y))
		return (1);
	return (0);
}
