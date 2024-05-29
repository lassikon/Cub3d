/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:58 by jberay            #+#    #+#             */
/*   Updated: 2024/05/29 09:41:32 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_entry(t_error_entry *errors)
{
	errors[0] = (t_error_entry){MSG_MALLOC, MALLOC_ERR};
	errors[1] = (t_error_entry){MSG_ARG, ARG_ERR};
	errors[2] = (t_error_entry){MSG_FILE_EXT, FILE_EXT_ERR};
	errors[3] = (t_error_entry){MSG_FILE_OPEN, FILE_OPEN_ERR};
	errors[4] = (t_error_entry){MSG_SCENE_FORMAT, SCENE_FORMAT_ERR};
	errors[5] = (t_error_entry){MSG_INVALID_MAP, INVALID_MAP_ERR};
	errors[6] = (t_error_entry){MSG_MAP_NOT_CLOSED, MAP_NOT_CLOSED_ERR};
	errors[7] = (t_error_entry){MSG_INVALID_PLAYER, INVALID_PLAYER_ERR};
	errors[8] = (t_error_entry){MSG_MAP_BIG, MAP_BIG_ERR};
	errors[9] = (t_error_entry){MSG_ENEMIES, ENEMIES_ERR};
}

void	error_handler(t_scene *scene, t_err_code code)
{
	t_error_entry	errors[10];
	int				i;

	init_entry(errors);
	i = 0;
	while (i < 10)
	{
		if (errors[i].code == code)
		{
			if (scene)
				free_scene(scene);
			ft_putstr_fd(errors[i].message, 2);
			exit(code);
		}
		i++;
	}
}

void	mlx_error_exit(t_game *game, t_scene *scene)
{
	mlx_terminate(game->mlx);
	if (scene)
		delete_textures(scene);
	if (scene)
		free_scene(scene);
	exit(1);
}
