/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:47:22 by jberay            #+#    #+#             */
/*   Updated: 2024/05/05 13:05:21 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_color(t_scene *scene, t_list **head, int *color)
{
	int		i;
	int		j;
	char	**split;
	char	*line;

	i = 0;
	j = 0;
	line = substr_guard(scene, head);
	split = ft_split(line, ',');
	malloc_guard(scene, head, NULL, split);
	free(line);
	while (split[i])
	{
		color[j] = ft_atoi(split[i]);
		if (color[j] < 0 || color[j] > 255)
			error_handler(scene, FREE_SCENE, SCENE_FORMAT_ERR);
		i++;
		j++;
	}
	free_arr(&split);
}

static void	parse_map(t_scene *scene, t_list **head)
{
	int		map_size;
	t_list	*tmp;
	size_t	t_longest_row;
	size_t	i;

	map_size = ft_lstsize(*head);
	printf("map_size: %d\n", map_size);
	scene->map = ft_calloc(map_size + 1, sizeof(char *));
	malloc_guard(scene, head, NULL, scene->map);
	tmp = *head;
	t_longest_row = 0;
	while (tmp)
	{
		if (((t_token *)tmp->content)->location.len > t_longest_row)
			t_longest_row = ((t_token *)tmp->content)->location.len;
		tmp = tmp->next;
	}
	i = 0;
	tmp = *head;
	while (tmp)
	{
		write_map(scene, head, i, t_longest_row);
		*head = (*head)->next;
		i++;
	}
	scene->map[i] = NULL;
}

static void	parse_texture(t_scene *scene, t_list **head)
{
	t_type	t_type;

	t_type = ((t_token *)(*head)->content)->type;
	if (t_type == NO)
		scene->no_texture = substr_guard(scene, head);
	else if (t_type == SO)
		scene->so_texture = substr_guard(scene, head);
	else if (t_type == WE)
		scene->we_texture = substr_guard(scene, head);
	else if (t_type == EA)
		scene->ea_texture = substr_guard(scene, head);
}

static void	write_data(t_scene *scene, t_list **head)
{
	t_type	t_type;

	t_type = ((t_token *)(*head)->content)->type;
	if (t_type == NO || t_type == SO || t_type == WE || t_type == EA)
		parse_texture(scene, head);
	else if (t_type == F)
		parse_color(scene, head, scene->floor_color);
	else if (t_type == C)
		parse_color(scene, head, scene->ceiling_color);
	else
		parse_map(scene, head);
}

void	extract_data(t_scene *scene, t_list **head)
{
	size_t	longest_row;
	int		j;
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		write_data(scene, &tmp);
		if (tmp)
			tmp = tmp->next;
	}
	if (head)
		free_lst(head);
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
