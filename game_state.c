/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:35:10 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/29 15:49:03 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_over(t_game *game)
{
	if (game->keep_playing)
		return ;
	if (game->p.hp == 0)
	{
		game->over = true;
		game->game_over_img->instances[0].enabled = true;
	}
	else if (!game->keep_playing && all_enemies_dead(game))
	{
		game->victory = true;
		game->win_img->instances[0].enabled = true;
	}
	if (game->victory && mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
	{
		game->keep_playing = true;
		game->victory = false;
		game->win_img->instances[0].enabled = false;
	}
}

int	all_enemies_dead(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->e[i].alive)
			return (0);
		i++;
	}
	return (1);
}

void	hitpoints(t_game *game, double frame)
{
	if (game->over)
		return ;
	if (game->p.regen_cooldown > 0)
		game->p.regen_cooldown--;
	if (game->p.hp < 90 && (int)frame % 40 == 0 && game->p.regen_cooldown == 0)
		game->p.hp += 10;
	disable_img_frames(game->hp_imgs, 10);
	if (game->p.hp < 80)
		game->hp_imgs[(game->p.hp / 8)]->enabled = true;
}
