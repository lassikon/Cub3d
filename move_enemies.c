/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:47:40 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/29 10:02:03 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hitpoints(t_game *game, double frame)
{
	char	hp[4];

	ft_memset(hp, 0, 4);
	ft_itoa_stack(hp, game->p.hp);
	if (game->hp_img)
		mlx_delete_image(game->mlx, game->hp_img);
	game->hp_img = mlx_put_string(game->mlx, hp, 10, 10);
	if (game->p.hp < 90 && (int)frame % 40 == 0)
		game->p.hp += 10;
	disable_img_frames(game->hp_imgs, 10);
	if (game->p.hp < 80)
		game->hp_imgs[(game->p.hp / 8)]->enabled = true;
}

void	enemy_attack(t_game *game, int id)
{
	if ((int)game->e[id].distance < E_SIZE * 2
		&& game->e[id].dying == 0 && game->p.hp > 0)
	{
		if (game->e[id].attacking == 0)
			game->e[id].attacking = 1;
		if (game->e[id].attacking == 18 && game->p.hp > 20)
			game->p.hp -= 20;
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
