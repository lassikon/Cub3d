/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:47:22 by jberay            #+#    #+#             */
/*   Updated: 2024/05/03 14:49:49 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	malloc_guard_scene(scene, head, NULL, substr);
	return (substr);
}

static void	write_map(t_scene *scene, t_list **head, \
	int i, size_t t_longest_row)
{
	char	*t_line;
	t_type	t_type;
	size_t	t_len;
	size_t	t_start;

	t_line = ((t_token *)(*head)->content)->line;
	t_type = ((t_token *)(*head)->content)->type;
	t_len = ((t_token *)(*head)->content)->location.len;
	t_start = ((t_token *)(*head)->content)->location.start;
	if (t_type == MAP)
	{
		scene->map[i] = ft_calloc(t_longest_row + 1, sizeof(char));
		malloc_guard_scene(scene, head, &scene->map, scene->map[i]);
		ft_memcpy(scene->map[i], t_line + t_start, t_len);
		printf("map: %s\n", scene->map[i]);
	}
}

void	parse_color(t_scene *scene, t_list **head, int *color)
{
	int		i;
	int		j;
	char	**split;
	char	*line;

	i = 0;
	j = 0;
	line = substr_guard(scene, head);
	split = ft_split(line, ',');
	malloc_guard_scene(scene, head, NULL, split);
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


void	parse_map(t_scene *scene, t_list **head)
{
	int		map_size;
	t_list	*tmp;
	size_t	t_longest_row;
	size_t	i;

	map_size = ft_lstsize(*head);
	scene->map = ft_calloc(map_size + 1, sizeof(char *));
	malloc_guard_scene(scene, head, NULL, scene->map);
	tmp = *head;
	t_longest_row = 0;
	while (tmp)
	{
		if (((t_token *)tmp->content)->location.len > t_longest_row)
			t_longest_row = ((t_token *)tmp->content)->location.len;
		tmp = tmp->next;
	}
	i = 0;
	while (*head)
	{
		write_map(scene, head, i, t_longest_row);
		*head = (*head)->next;
		i++;
	}
	scene->map[i] = NULL;
}

static int	check_texture(t_scene *scene)
{
	if (scene->no_texture == NULL)
		return (0);
	if (scene->so_texture == NULL)
		return (0);
	if (scene->we_texture == NULL)
		return (0);
	if (scene->ea_texture == NULL)
		return (0);
	if (scene->floor_color[0] == -1 || scene->floor_color[1] == -1
		|| scene->floor_color[2] == -1)
		return (0);
	if (scene->ceiling_color[0] == -1 || scene->ceiling_color[1] == -1
		|| scene->ceiling_color[2] == -1)
		return (0);
	return (1);
}


void	parse_texture(t_scene *scene, t_list **head)
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

void	write_data(t_scene *scene, t_list **head)
{
	t_type	t_type;

	t_type = ((t_token *)(*head)->content)->type;
	if (t_type == NO || t_type == SO || t_type == WE || t_type == EA)
		parse_texture(scene, head);
	else if (t_type == F)
		parse_color(scene, head, scene->floor_color);
	else if (t_type == C)
		parse_color(scene, head, scene->ceiling_color);
	else if (t_type == MAP && check_texture(scene))
		parse_map(scene, head);
	else
		error_handler(scene, SCENE_FORMAT_ERR);
}
