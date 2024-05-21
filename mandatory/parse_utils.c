/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:28:19 by jberay            #+#    #+#             */
/*   Updated: 2024/05/21 14:07:17 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	write_map(t_scene *scene, t_list *lst_iter, int i)
{
	char	*t_line;
	t_type	t_type;
	size_t	t_len;
	size_t	t_start;

	t_line = ((t_token *)(lst_iter)->content)->line;
	t_type = ((t_token *)(lst_iter)->content)->type;
	t_len = ((t_token *)(lst_iter)->content)->location.len;
	t_start = ((t_token *)(lst_iter)->content)->location.start;
	if (t_type == MAP)
	{
		scene->map[i] = ft_calloc(scene->map_width + 1, sizeof(char));
		malloc_guard(scene, &scene->map, scene->map[i]);
		ft_memcpy(scene->map[i], t_line + t_start, t_len);
	}
}
