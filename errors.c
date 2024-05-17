/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:58 by jberay            #+#    #+#             */
/*   Updated: 2024/05/16 10:25:55 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_entry(t_error_entry *errors)
{
	errors[0] = (t_error_entry){"Error\nMalloc failed\n", MALLOC_ERR};
	errors[1] = (t_error_entry){"Error\nInvalid arguments\n", ARG_ERR};
	errors[2] = (t_error_entry){"Error\nInvalid file extension\n", FILE_EXT_ERR};
	errors[3] = (t_error_entry){"Error\nFailed to open file\n", FILE_OPEN_ERR};
	errors[4] = (t_error_entry){"Error\nInvalid scene format\n", SCENE_FORMAT_ERR};
	errors[5] = (t_error_entry){"Error\nFound invalid map characters\n", INVALID_MAP_ERR};
	errors[6] = (t_error_entry){"Error\nMap is not closed\n", MAP_NOT_CLOSED_ERR};
	errors[7] = (t_error_entry){"Error\nInvalid player\n", INVALID_PLAYER_ERR};
	errors[8] = (t_error_entry){"Error\nMap too big\n", MAP_BIG_ERR};
}

void	error_handler(t_scene *scene, t_err_code code)
{
	t_error_entry	errors[9];
	int				i;

	init_entry(errors);
	i = 0;
	while (i < 9)
	{
		if (errors[i].code == code)
		{
			free_scene(scene);
			ft_putstr_fd(errors[i].message, 2);
			exit(code);
		}
		i++;
	}
}
