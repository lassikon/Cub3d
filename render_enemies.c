/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:42:42 by jberay            #+#    #+#             */
/*   Updated: 2024/05/24 16:05:54 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_enemy_tx_ty(t_game *game, t_ray *eray, float ratio, int i)
{
	eray->ty = 0;
	eray->ty_step = (float)game->e[i].img[0]->height / eray->height;
	game->render.e_bottom = (ratio * game->p.height) + game->vertical_center;
	game->render.e_top = game->render.e_bottom - eray->height;
	if (game->render.e_top < 0)
	{
		eray->ty += -game->render.e_top * eray->ty_step;
		game->render.e_top = 0;
	}
	if (game->render.e_bottom >= SCREEN_HEIGHT)
		game->render.e_bottom = SCREEN_HEIGHT - 1;
	eray->ty_step = fmod(eray->ty_step, game->e[i].img[0]->height);
	eray->tx_step = (float)game->e[i].img[0]->width / eray->height;
	eray->tx = 0;
	game->render.e_left = -eray->height / 2 + eray->sprite_screen_x;
	game->render.e_right = eray->height / 2 + eray->sprite_screen_x;
	if (game->render.e_left < 0)
	{
		eray->tx += -game->render.e_left * eray->tx_step;
		game->render.e_left = 0;
	}
	if (game->render.e_right >= SCREEN_WIDTH)
		game->render.e_right = SCREEN_WIDTH - 1;
	eray->tx_step = fmod(eray->tx_step, game->e[i].img[0]->width);
}

static void	get_enemy_x_y(t_game *game, t_ray *eray, int i)
{
	float	rel_x;
	float	rel_y;
	int		trigtable;
	float	ratio;

	trigtable = (int)(game->p.angle * game->math.trig_it);
	rel_x = game->e[i].x - game->p.x;
	rel_y = game->e[i].y - game->p.y;
	eray->x = rel_y * game->math.cos[trigtable] \
		- rel_x * game->math.sin[trigtable];
	eray->y = rel_y * game->math.sin[trigtable] \
		+ rel_x * game->math.cos[trigtable];
	eray->distance = sqrtf(eray->x * eray->x + eray->y * eray->y);
	if (eray->y <= 0)
		return ;
	ratio = game->dist_to_proj_plane / eray->distance;
	eray->sprite_screen_x = (int)((SCREEN_WIDTH / 2) \
		+ ((eray->x * game->dist_to_proj_plane) / eray->y));
	eray->height = (int)((E_HEIGHT / eray->distance) \
		* game->dist_to_proj_plane);
	eray->wall_side = NORTH;
	get_enemy_tx_ty(game, eray, ratio, i);
}

static void	render_image(t_game *game, t_ray *eray, int i, int frame)
{
	int		row;
	float	tx_tmp;

	tx_tmp = eray->tx;
	row = game->render.e_top;
	while (row < game->render.e_bottom)
	{
		eray->tx = tx_tmp;
		eray->column = game->render.e_left;
		while (eray->column < game->render.e_right
			&& (eray->distance < game->rays[eray->column].distance))
		{
			put_texture_pixel(game, eray, game->e[i].img[frame], row);
			eray->tx += eray->tx_step;
			if (eray->tx >= game->e[i].img[frame]->width)
				break ;
			eray->column++;
		}
		eray->ty += eray->ty_step;
		if (eray->ty >= game->e[i].img[frame]->height)
			break ;
		row++;
	}
}

void	next_enemy_to_render(t_game *game)
{
	int		i;
	float	rel_x;
	float	rel_y;
	float	distance;

	i = 0;
	distance = 0;
	game->next_enemy_to_render = -1;
	while (i < game->enemy_count)
	{
		if (game->e[i].rendered == false)
		{
			rel_x = game->e[i].x - game->p.x;
			rel_y = game->e[i].y - game->p.y;
			game->e[i].distance = sqrtf(rel_x * rel_x + rel_y * rel_y);
			if (game->e[i].distance > distance)
			{
				distance = game->e[i].distance;
				game->next_enemy_to_render = i;
			}
		}
		i++;
	}
}

void	render_enemy(t_game *game, int i, int frame)
{
	t_ray	eray;

	if (game->e[i].alive == false)
		return ;
	get_enemy_x_y(game, &eray, i);
	if (eray.y <= 0)
		return ;
	get_brightness_lvl(game, &eray);
	render_image(game, &eray, i, frame);
	if (SCREEN_WIDTH / 2 > game->render.e_left
		&& SCREEN_WIDTH / 2 < game->render.e_right)
	{
		if (SCREEN_HEIGHT / 2 > game->render.e_top
			&& SCREEN_HEIGHT / 2 < game->render.e_bottom)
			game->in_crosshairs_id = i;
	}
}
