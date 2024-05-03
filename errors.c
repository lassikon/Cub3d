/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:58 by jberay            #+#    #+#             */
/*   Updated: 2024/05/03 14:08:39 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exec(t_scene *scene, char *message, t_err_code code)
{
	free_scene(scene);
	ft_putstr_fd(message, 2);
	exit(code);

}

void	init_entry(t_error_entry *errors)
{

	errors[0] = (t_error_entry){"Error\nMalloc failed\n", MALLOC_ERR};
	errors[1] = (t_error_entry){"Error\nInvalid arguments\n", ARG_ERR};
	errors[2] = (t_error_entry){"Error\nInvalid file extension\n", FILE_EXT_ERR};
	errors[3] = (t_error_entry){"Error\nFailed to open file\n", FILE_OPEN_ERR};
	errors[4] = (t_error_entry){"Error\nInvalid scene format\n", SCENE_FORMAT_ERR};
	errors[5] = (t_error_entry){"Error\nMap is not closed\n", MAP_NOT_CLOSED_ERR};
}

void	error_handler(t_scene *scene, t_err_code code)
{
	t_error_entry	errors[4];
	//t_error_handler	handler;
	int				i;

	init_entry(errors);
	i = 0;
	while (i < 6)
	{
		if (errors[i].code == code)
		{
			error_exec(scene, errors[i].message, code);
		}
		i++;
	}
}
