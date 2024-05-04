/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:58 by jberay            #+#    #+#             */
/*   Updated: 2024/05/04 10:49:57 by janraub          ###   ########.fr       */
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
}

void	error_handler(void *data, t_free_func func, t_err_code code)
{
	t_error_entry	errors[7];
	int				i;

	init_entry(errors);
	i = 0;
	while (i < 7)
	{
		if (errors[i].code == code)
		{
			if (func == FREE_SCENE)
				free_scene((t_scene *)data);
			else if (func == FREE_LST)
				free_lst((t_list **)data);
			else if (func == FREE_ARR)
				free_arr((char ***)data);
			else if (func == FREE)
				free((char *)data);
			else
				(void)data;
			ft_putstr_fd(errors[i].message, 2);
			exit(code);
		}
		i++;
	}
}
