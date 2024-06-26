/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemies_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:47:40 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 12:10:36 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	enemy_attack(t_game *game, int id)
{
	if ((int)game->e[id].distance < E_SIZE * 2
		&& game->e[id].dying == 0 && game->p.hp > 0)
	{
		if (game->e[id].attacking == 0)
			game->e[id].attacking = 1;
		if (game->e[id].attacking == 18 && game->p.hp > 0)
		{
			game->p.hp -= 20;
			if (game->p.hp < 0)
				game->p.hp = 0;
			game->p.regen_cooldown = 80;
		}
	}
}

static int	enemy_collision(t_game *game, int x, int y, int id)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->e[i].alive && i != id)
		{
			if (game->e[i].x > x - E_SIZE && game->e[i].x < x + E_SIZE
				&& game->e[i].y > y - E_SIZE
				&& game->e[i].y < y + E_SIZE)
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
		if (!move_collision(game, (int)e->x - ENEMY_SPEED - E_SIZE, (int)e->y)
			&& !enemy_collision(game, (int)e->x - ENEMY_SPEED, (int)e->y, id))
			e->x -= ENEMY_SPEED;
	if (e->x < game->p.x)
		if (!move_collision(game, (int)e->x + ENEMY_SPEED + E_SIZE, (int)e->y)
			&& !enemy_collision(game, (int)e->x + ENEMY_SPEED, (int)e->y, id))
			e->x += ENEMY_SPEED;
	if (e->y > game->p.y)
		if (!move_collision(game, (int)e->x, (int)e->y - ENEMY_SPEED - E_SIZE)
			&& !enemy_collision(game, (int)e->x, (int)e->y - ENEMY_SPEED, id))
			e->y -= ENEMY_SPEED;
	if (e->y < game->p.y)
		if (!move_collision(game, (int)e->x, (int)e->y + ENEMY_SPEED + E_SIZE)
			&& !enemy_collision(game, (int)e->x, (int)e->y + ENEMY_SPEED, id))
			e->y += ENEMY_SPEED;
}

void	move_enemies(t_game *game)
{
	int	i;

	i = 0;
	if (game->over || game->victory || game->keep_playing)
		return ;
	while (i < game->enemy_count)
	{
		if (game->e[i].alive && game->e[i].dying == 0)
		{
			if (game->e[i].attacking == 0)
				move_one_enemy(game, &game->e[i], i);
			else
				game->e[i].attacking++;
			if (game->e[i].attacking > 18)
				game->e[i].attacking = 0;
		}
		i++;
	}
}
