/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_vertical_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:44:19 by lkonttin          #+#    #+#             */
/*   Updated: 2024/05/30 11:07:12 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	crouch(t_game *game)
{
	if (game->p.height > 16)
		game->p.height -= 4;
}

static void	stand_up(t_game *game)
{
	if (game->p.height < TILE / 2)
		game->p.height += 4;
	if (game->p.height > TILE / 2)
		game->p.height = TILE / 2;
}

static void	jump(t_game *game)
{
	if (game->p.jumping < 14)
		game->p.height = game->p.jump_height[game->p.jumping];
	game->p.jumping++;
	if (game->p.jumping == 14)
		game->p.jumping = 0;
}

void	move_player_vertical(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP)
		&& game->vertical_center < SCREEN_HEIGHT - 20)
		game->vertical_center += 20;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN) && game->vertical_center > 20)
		game->vertical_center -= 20;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL) && !game->p.jumping)
		crouch(game);
	else if (!game->p.jumping && game->p.height < TILE / 2)
		stand_up(game);
	if (!game->p.jumping && mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		game->p.jumping = 1;
	if (game->p.jumping > 0)
		jump(game);
}
