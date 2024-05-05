/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:28:19 by jberay            #+#    #+#             */
/*   Updated: 2024/05/05 12:51:31 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	malloc_guard(t_scene *scene, t_list **head, char ***tmp, void *ptr)
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
		printf("map: %s\n", array[i]);
		i++;
	}
}

void print_list(t_list *head)
{
	t_list	*tmp;
	t_token	*token;

	tmp = head;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		printf("line: %s\n", token->line);
		printf("type: %d\n", token->type);
		printf("start: %zu\n", token->location.start);
		printf("len: %zu\n", token->location.len);
		tmp = tmp->next;
	}
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
	malloc_guard(scene, head, NULL, substr);
	return (substr);
}

void	write_map(t_scene *scene, t_list **head, \
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
		malloc_guard(scene, head, &scene->map, scene->map[i]);
		ft_memcpy(scene->map[i], t_line + t_start, t_len);
	}
}
