/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:28:19 by jberay            #+#    #+#             */
/*   Updated: 2024/05/29 09:53:57 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_scene(t_scene *scene)
{
	scene->no_texture = NULL;
	scene->so_texture = NULL;
	scene->we_texture = NULL;
	scene->ea_texture = NULL;
	scene->dr_texture = NULL;
	scene->dr_texture = NULL;
	scene->fl_texture = NULL;
	scene->cl_texture = NULL;
	ft_memset(scene->floor_color, -1, 3);
	ft_memset(scene->ceiling_color, -1, 3);
	scene->map = NULL;
	scene->tokens = NULL;
	scene->map_height = 0;
	scene->map_width = 0;
}

void	malloc_guard(t_scene *scene, char ***tmp, void *ptr)
{
	if (ptr == NULL)
	{
		if (*tmp != NULL)
			free_arr(tmp);
		error_handler(scene, MALLOC_ERR);
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

char	*substr_guard(t_scene *scene, t_list **head)
{
	char	*t_line;
	size_t	t_len;
	size_t	t_start;
	char	*substr;

	t_line = ((t_token *)(*head)->content)->line;
	t_len = ((t_token *)(*head)->content)->location.len;
	t_start = ((t_token *)(*head)->content)->location.start;
	substr = ft_substr(t_line, t_start, t_len);
	malloc_guard(scene, NULL, substr);
	return (substr);
}

int	is_arrdigit(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (!ft_isdigit(arr[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}
