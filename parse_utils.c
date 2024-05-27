/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:28:19 by jberay            #+#    #+#             */
/*   Updated: 2024/05/27 09:31:11 by jberay           ###   ########.fr       */
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

void	ft_itoa_stack(char *buf, int n)
{
	long	nbl;
	size_t	len;

	nbl = n;
	len = 1;
	while (n / 10 >= 1)
	{
		n = n / 10;
		len++;
	}
	while (len > 0)
	{
		buf[len - 1] = nbl % 10 + 48;
		nbl = nbl / 10;
		len--;
	}
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

void print_array(char **array)
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
		printf("########\n");
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
