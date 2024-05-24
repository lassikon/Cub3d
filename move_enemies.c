/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:47:40 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/24 16:42:50 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	enemy_collision(t_game *game, int x, int y, int id)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->e[i].alive && i != id)
		{
			if (game->e[i].x > x - ENEMY_SIZE && game->e[i].x < x + ENEMY_SIZE
				&& game->e[i].y > y - ENEMY_SIZE
				&& game->e[i].y < y + ENEMY_SIZE)
				return (1);
		}
		i++;
	}
	return (0);
}

static void	move_one_enemy(t_game *game, t_enemy *e, int id)
{
	if (e->x < 0 || e->x >= game->map_width
		|| e->y < 0 || e->y >= game->map_height)
		return ;
	if (e->x > game->p.x)
		if (!move_x_collision(game, (int)e->x - ENEMY_SPEED, (int)e->y)
			&& !enemy_collision(game, (int)e->x - ENEMY_SPEED, (int)e->y, id))
			e->x -= ENEMY_SPEED;
	if (e->x < game->p.x)
		if (!move_x_collision(game, (int)e->x + ENEMY_SPEED, (int)e->y)
			&& !enemy_collision(game, (int)e->x + ENEMY_SPEED, (int)e->y, id))
			e->x += ENEMY_SPEED;
	if (e->y > game->p.y)
		if (!move_y_collision(game, (int)e->x, (int)e->y - ENEMY_SPEED)
			&& !enemy_collision(game, (int)e->x, (int)e->y - ENEMY_SPEED, id))
			e->y -= ENEMY_SPEED;
	if (e->y < game->p.y)
		if (!move_y_collision(game, (int)e->x, (int)e->y + ENEMY_SPEED)
			&& !enemy_collision(game, (int)e->x, (int)e->y + ENEMY_SPEED, id))
			e->y += ENEMY_SPEED;
}

void	move_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		move_one_enemy(game, &game->e[i], i);
		i++;
	}
}
