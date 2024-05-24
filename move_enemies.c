/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:47:40 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/24 14:56:43 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_one_enemy(t_game *game, t_enemy *e)
{
	if (e->x < 0 || e->x >= game->map_width
		|| e->y < 0 || e->y >= game->map_height)
		return ;
	if (e->x > game->p.x)
		if (!move_x_collision(game, (int)e->x - ENEMY_SPEED, (int)e->y))
			e->x -= ENEMY_SPEED;
	if (e->x < game->p.x)
		if (!move_x_collision(game, (int)e->x + ENEMY_SPEED, (int)e->y))
			e->x += ENEMY_SPEED;
	if (e->y > game->p.y)
		if (!move_y_collision(game, (int)e->x, (int)e->y - ENEMY_SPEED))
			e->y -= ENEMY_SPEED;
	if (e->y < game->p.y)
		if (!move_y_collision(game, (int)e->x, (int)e->y + ENEMY_SPEED))
			e->y += ENEMY_SPEED;
}

void	move_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		move_one_enemy(game, &game->e[i]);
		i++;
	}
}
