/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:16:45 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/07 15:28:48 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BPP sizeof(int32_t)

void	minimap_rays(t_game *game, t_minimap *m)
{
	float	x;
	float	y;
	float	angle;
	int		angle_steps;

	angle = game->p.angle - FOV / 2;
	if (angle < 0)
		angle += PI * 2;
	angle_steps = 0;
	while (angle_steps < 150)
	{
		m->x = MINIMAP_SIZE / 2;
		m->y = MINIMAP_SIZE / 2;
		while (1)
		{
			mlx_put_pixel(game->mini_img, (int)m->x, (int)m->y, 0xA0A0A0FF);
			m->x += cos(angle) * 0.5f;
			m->y += sin(angle) * 0.5f;
			if (m->x < 0 || m->x >= MINIMAP_SIZE || m->y < 0 || m->y >= MINIMAP_SIZE)
				break ;
			x = game->p.x + (m->x - MINIMAP_SIZE / 2) * 4;
			y = game->p.y + (m->y - MINIMAP_SIZE / 2) * 4;
			if (game->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
				break ;
		}
		angle_steps++;
		angle += FOV / 150;
		if (angle > PI * 2)
			angle -= PI * 2;
	}
}

void	minimap(t_game *game)
{
	float		i;
	float		k;
	t_minimap	m;

	m = game->minimap;
	m.x = 0;
	m.y = 0;
	i = game->p.x - MINIMAP_SIZE * 2;
	k = game->p.y - MINIMAP_SIZE * 2;
	while (m.y < MINIMAP_SIZE)
	{
		while (m.x < MINIMAP_SIZE)
		{
			if (i < 0 || i >= game->map_width || k < 0 || k >= game->map_height)
				mlx_put_pixel(game->mini_img, m.x, m.y, 0x404040FF);
			else if (m.x > (MINIMAP_SIZE / 2 - 4) && m.x < (MINIMAP_SIZE / 2 + 4)
				&& m.y > (MINIMAP_SIZE / 2 - 4) && m.y < (MINIMAP_SIZE / 2 + 4))
				mlx_put_pixel(game->mini_img, m.x, m.y, 0xFF0000FF); //red
			else if (game->map[(int)(k / TILE_SIZE)][(int)(i / TILE_SIZE)]
				&& game->map[(int)(k / TILE_SIZE)][(int)(i / TILE_SIZE)] == '1')
				mlx_put_pixel(game->mini_img, m.x, m.y, 0x000000FF); //black
			else
				mlx_put_pixel(game->mini_img, m.x, m.y, 0x404040FF);
			i += 4;
			m.x++;
		}
		i = game->p.x - MINIMAP_SIZE * 2;
		m.x = 0;
		k += 4;
		m.y++;
	}
	minimap_rays(game, &m);
}
