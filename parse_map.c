/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:47:22 by jberay            #+#    #+#             */
/*   Updated: 2024/05/05 15:52:36 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_color(t_scene *scene, t_list **lst_iter, int *color)
{
	int		i;
	int		j;
	char	**split;
	char	*line;

	i = 0;
	j = 0;
	line = substr_guard(scene, lst_iter);
	split = ft_split(line, ',');
	malloc_guard(scene, NULL, split);
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
	size_t	t_longest_row;
	size_t	i;

	map_size = ft_lstsize(*map_head);
	scene->map = ft_calloc(map_size + 1, sizeof(char *));
	malloc_guard(scene, NULL, scene->map);
	lst_iter = *map_head;
	t_longest_row = 0;
	while (lst_iter)
	{
		if (((t_token *)lst_iter->content)->location.len > t_longest_row)
			t_longest_row = ((t_token *)lst_iter->content)->location.len;
		lst_iter = lst_iter->next;
	}
	i = 0;
	while (*map_head)
	{
		write_map(scene, *map_head, i, t_longest_row);
		*map_head = (*map_head)->next;
		i++;
	}
	scene->map[i] = NULL;
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

static void	write_data(t_scene *scene, t_list **lst_iter)
{
	t_type	t_type;

	t_type = ((t_token *)(*lst_iter)->content)->type;
	if (t_type == NO || t_type == SO || t_type == WE || t_type == EA)
		parse_texture(scene, lst_iter);
	else if (t_type == F)
		parse_color(scene, lst_iter, scene->floor_color);
	else if (t_type == C)
		parse_color(scene, lst_iter, scene->ceiling_color);
	else
		parse_map(scene, lst_iter);
}

void	extract_data(t_scene *scene)
{
	size_t	longest_row;
	int		j;
	t_list	*lst_iter;

	lst_iter = scene->tokens;
	while (lst_iter)
	{
		write_data(scene, &lst_iter);
		if (lst_iter)
			lst_iter = lst_iter->next;
	}
	longest_row = 0;
	j = 0;
	while (scene->map[j])
	{
		if (ft_strlen(scene->map[j]) > longest_row)
			longest_row = ft_strlen(scene->map[j]);
		j++;
	}
	is_valid(scene, longest_row);
}
