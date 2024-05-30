/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemies_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:42:42 by jberay            #+#    #+#             */
/*   Updated: 2024/05/30 11:07:42 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static mlx_image_t	*choose_enemy_img(t_game *game, int i, int frame)
{
	mlx_image_t	*img;

	if (game->e[i].attacking > 0)
		img = game->e[i].aimg[game->e[i].attacking / 6];
	else if (game->e[i].dying == 0)
		img = game->e[i].img[frame / 4];
	else
	{
		img = game->e[i].dimg[(game->e[i].dying - 1) / 2];
		game->e[i].dying++;
		if (game->e[i].dying > 18)
			game->e[i].alive = false;
	}
	return (img);
}

static void	render_image(t_game *game, t_ray *eray, int i, int frame)
{
	int			row;
	float		tx_tmp;
	mlx_image_t	*img;

	tx_tmp = eray->tx;
	row = game->render.e_top;
	img = choose_enemy_img(game, i, frame);
	while (row < game->render.e_bottom)
	{
		eray->tx = tx_tmp;
		eray->column = game->render.e_left;
		while (eray->column < game->render.e_right)
		{
			if (eray->distance < game->rays[eray->column].distance)
				put_texture_pixel(game, eray, img, row);
			eray->tx += eray->tx_step;
			if (eray->tx >= img->width)
				break ;
			eray->column++;
		}
		eray->ty += eray->ty_step;
		if (eray->ty >= img->height)
			break ;
		row++;
	}
}

static void	render_enemy(t_game *game, int i, int frame)
{
	t_ray	eray;

	if (game->e[i].alive == false || game->e[i].rendered == true)
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

static void	next_enemy_to_render(t_game *game)
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
		if (game->e[i].rendered == false && game->e[i].alive == true)
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
	if (game->next_enemy_to_render >= 0)
		enemy_attack(game, game->next_enemy_to_render);
}

void	render_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		next_enemy_to_render(game);
		if (game->next_enemy_to_render != -1)
		{
			render_enemy(game, game->next_enemy_to_render, \
			((int)game->frame_count % 16));
			game->e[game->next_enemy_to_render].rendered = true;
		}
		i++;
	}
}
