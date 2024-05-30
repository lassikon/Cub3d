/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:47:22 by jberay            #+#    #+#             */
/*   Updated: 2024/05/30 11:49:21 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_arrdigit(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (!ft_isdigit(arr[i][j]) || j > 3)
				return (1);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

static void	parse_color(t_scene *scene, t_list **lst_iter, int *color)
{
	int		i;
	int		j;
	char	**split;
	char	*line;

	i = 0;
	j = 0;
	line = substr_guard(scene, lst_iter);
	if (ft_strnstr(line, ",,", ft_strlen(line)) != NULL
		|| line[0] == ',' || line[ft_strlen(line) - 1] == ',')
		error_handler(scene, SCENE_FORMAT_ERR);
	split = ft_split(line, ',');
	malloc_guard(scene, NULL, split);
	if (is_arrdigit(split))
		error_handler(scene, SCENE_FORMAT_ERR);
	free(line);
	while (split[i])
	{
		color[j] = ft_atoi(split[i]);
		if (color[j] < 0 || color[j] > 255)
			error_handler(scene, SCENE_FORMAT_ERR);
		i++;
		j++;
	}
	free_arr(&split);
}

static void	parse_map(t_scene *scene, t_list **map_head)
{
	int		map_size;
	t_list	*lst_iter;
	size_t	i;
	size_t	t_len;

	map_size = ft_lstsize(*map_head);
	scene->map = ft_calloc(map_size + 1, sizeof(char *));
	malloc_guard(scene, NULL, scene->map);
	lst_iter = *map_head;
	while (lst_iter)
	{
		t_len = ((t_token *)lst_iter->content)->location.len;
		if (t_len > (size_t)scene->map_width)
			scene->map_width = ((t_token *)lst_iter->content)->location.len;
		lst_iter = lst_iter->next;
	}
	i = 0;
	while (*map_head)
	{
		write_map(scene, *map_head, i);
		*map_head = (*map_head)->next;
		i++;
	}
	scene->map[i] = NULL;
	scene->map_height = i;
}

static void	parse_texture(t_scene *scene, t_list **lst_iter)
{
	t_type	t_type;

	t_type = ((t_token *)(*lst_iter)->content)->type;
	if (t_type == NO)
		scene->no_texture = substr_guard(scene, lst_iter);
	else if (t_type == SO)
		scene->so_texture = substr_guard(scene, lst_iter);
	else if (t_type == WE)
		scene->we_texture = substr_guard(scene, lst_iter);
	else if (t_type == EA)
		scene->ea_texture = substr_guard(scene, lst_iter);
}

void	extract_data(t_scene *scene)
{
	t_list	*lst_iter;
	t_type	t_type;

	lst_iter = scene->tokens;
	while (lst_iter)
	{
		t_type = ((t_token *)(lst_iter)->content)->type;
		if (t_type == NO || t_type == SO || t_type == WE || t_type == EA)
			parse_texture(scene, &lst_iter);
		else if (t_type == F)
			parse_color(scene, &lst_iter, scene->floor_color);
		else if (t_type == C)
			parse_color(scene, &lst_iter, scene->ceiling_color);
		else if (t_type == MAP)
			parse_map(scene, &lst_iter);
		if (lst_iter)
			lst_iter = lst_iter->next;
	}
	is_valid(scene);
}
