/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:16:45 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/27 12:35:39 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_ray(t_game *game, t_minimap *m, float angle)
{
	int		ray_length;

	ray_length = 0;
	while (ray_length < 128)
	{
		mlx_put_pixel(game->mini_img, (int)m->x, (int)m->y, 0xA0A0A0FF);
		m->x += cos(angle) * 0.5f;
		m->y += sin(angle) * 0.5f;
		ray_length++;
		if (m->x < 0 || m->x > MINIMAP_SIZE || m->y < 0 || m->y > MINIMAP_SIZE)
			break ;
		m->map_x = game->p.x + (m->x - MINIMAP_SIZE / 2) * 4;
		m->map_y = game->p.y + (m->y - MINIMAP_SIZE / 2) * 4;
		if (m->map_x < 0 || m->map_x > game->map_width
			|| m->map_y < 0 || m->map_y > game->map_height)
			break ;
		if (!game->map[(int)(m->map_y / TILE)][(int)(m->map_x / TILE)]
			|| game->map[(int)(m->map_y / TILE)][(int)(m->map_x / TILE)] == '1'
			|| game->map[(int)(m->map_y / TILE)][(int)(m->map_x / TILE)] == '2')
			break ;
	}
}

static void	minimap_fov_rays(t_game *game, t_minimap *m)
{
	float	angle;
	int		angle_steps;

	angle = game->p.angle - FOV / 2;
	if (angle < 0)
		angle += PI * 2;
	angle_steps = 0;
	while (angle_steps < 100)
	{
		m->x = MINIMAP_SIZE / 2;
		m->y = MINIMAP_SIZE / 2;
		draw_minimap_ray(game, m, angle);
		angle_steps++;
		angle += FOV / 100;
		if (angle > PI * 2)
			angle -= PI * 2;
	}
}

static void	put_minimap_pixel(t_game *game, t_minimap *m)
{
	if (m->map_x < 0 || m->map_x >= game->map_width
		|| m->map_y < 0 || m->map_y >= game->map_height)
		mlx_put_pixel(game->mini_img, m->x, m->y, GREY);
	else if (m->x > (MINIMAP_SIZE / 2 - 4) && m->x < (MINIMAP_SIZE / 2 + 4)
		&& m->y > (MINIMAP_SIZE / 2 - 4) && m->y < (MINIMAP_SIZE / 2 + 4))
		mlx_put_pixel(game->mini_img, m->x, m->y, RED);
	else if (game->map[(int)(m->map_y / TILE)][(int)(m->map_x / TILE)]
		&& game->map[(int)(m->map_y / TILE)][(int)(m->map_x / TILE)] == '1')
		mlx_put_pixel(game->mini_img, m->x, m->y, BLACK);
	else if (game->map[(int)(m->map_y / TILE)][(int)(m->map_x / TILE)]
		&& game->map[(int)(m->map_y / TILE)][(int)(m->map_x / TILE)] == '2')
		mlx_put_pixel(game->mini_img, m->x, m->y, BROWN);
	else if (game->map[(int)(m->map_y / TILE)][(int)(m->map_x / TILE)]
		&& game->map[(int)(m->map_y / TILE)][(int)(m->map_x / TILE)] == '3')
		mlx_put_pixel(game->mini_img, m->x, m->y, OLIVE);
	else
		mlx_put_pixel(game->mini_img, m->x, m->y, GREY);
}

void	minimap(t_game *game)
{
	int	radius;
	int	distance;

	game->mini.y = 0;
	game->mini.map_y = game->p.y - MINIMAP_SIZE * 2;
	radius = 480;
	while (game->mini.y < MINIMAP_SIZE)
	{
		game->mini.x = 0;
		game->mini.map_x = game->p.x - MINIMAP_SIZE * 2;
		while (game->mini.x < MINIMAP_SIZE)
		{
			distance = sqrtf((game->p.x - game->mini.map_x) \
				* (game->p.x - game->mini.map_x) \
				+ (game->p.y - game->mini.map_y) \
				* (game->p.y - game->mini.map_y));
			if (distance < radius)
				put_minimap_pixel(game, &game->mini);
			game->mini.x++;
			game->mini.map_x += 4;
		}
		game->mini.y++;
		game->mini.map_y += 4;
	}
	minimap_fov_rays(game, &game->mini);
}
