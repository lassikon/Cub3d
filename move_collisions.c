/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_collisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:55:44 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/24 14:58:34 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_x_collision(t_game *game, int x, int y)
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

int	move_y_collision(t_game *game, int x, int y)
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
