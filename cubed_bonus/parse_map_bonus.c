/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:47:22 by jberay            #+#    #+#             */
/*   Updated: 2024/05/30 11:50:26 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static void	write_map(t_scene *scene, t_list *lst_iter, int i)
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
	else if (t_type == DR)
		scene->dr_texture = substr_guard(scene, lst_iter);
	else if (t_type == FL)
		scene->fl_texture = substr_guard(scene, lst_iter);
	else if (t_type == CL)
		scene->cl_texture = substr_guard(scene, lst_iter);
}

void	extract_data(t_scene *scene)
{
	t_list	*lst_iter;
	t_type	t_type;

	lst_iter = scene->tokens;
	while (lst_iter)
	{
		t_type = ((t_token *)(lst_iter)->content)->type;
		if (t_type == NO || t_type == SO || t_type == WE
			|| t_type == EA || t_type == DR || t_type == FL || t_type == CL)
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
	if (scene->map_height > 500 || scene->map_width > 500)
		error_handler(scene, MAP_BIG_ERR);
	is_valid(scene);
}
