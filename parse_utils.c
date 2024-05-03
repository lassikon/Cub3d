/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:28:19 by jberay            #+#    #+#             */
/*   Updated: 2024/05/03 13:40:29 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	malloc_guard_scene(t_scene *scene, t_list **head, char ***tmp, void *ptr)
{
	if (ptr == NULL)
	{
		if (*tmp != NULL)
			free_arr(tmp);
		if (head != NULL)
			free_lst(head);
		if (scene->map != NULL)
			free_scene(scene);
		ft_putstr_fd("Malloc failed\n", 2);
		exit(1);
	}
}

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	print_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("env: %s\n", array[i]);
		i++;
	}
}
