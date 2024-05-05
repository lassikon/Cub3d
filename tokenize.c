/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:47:03 by jberay            #+#    #+#             */
/*   Updated: 2024/05/05 13:43:26 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	take_textures(t_list **head, char *line, t_type type, size_t *iter)
{
	t_token	token;
	t_token	*tokenp;
	t_list	*new;

	token.line = line;
	*iter += 2;
	while (line[*iter] == ' ')
		*iter += 1;
	token.type = type;
	token.location.start = *iter;
	token.location.len = 0;
	while (line[*iter] != '\n' && line[*iter] != '\0')
	{
		(*iter)++;
		token.location.len++;
	}
	tokenp = malloc(sizeof(t_token));
	malloc_guard(NULL, head, NULL, tokenp);
	*tokenp = token;
	new = ft_lstnew(tokenp);
	malloc_guard(NULL, head, NULL, new);
	ft_lstadd_back(head, new);
}

static void	take_fc(t_list **head, char *line, t_type type, size_t *iter)
{
	t_token	token;
	t_token	*tokenp;
	t_list	*new;

	token.line = line;
	token.type = type;
	token.location.len = 0;
	*iter += 1;
	while (line[*iter] == ' ')
		*iter += 1;
	token.location.start = *iter;
	while (line[*iter] != '\n' && line[*iter] != '\0')
	{
		(*iter)++;
		token.location.len++;
	}
	tokenp = malloc(sizeof(t_token));
	malloc_guard(NULL, head, NULL, tokenp);
	*tokenp = token;
	new = ft_lstnew(tokenp);
	malloc_guard(NULL, head, NULL, new);
	ft_lstadd_back(head, new);
}

static void	take_map(t_list **head, char *line, t_type type, size_t *iter)
{
	t_token	token;
	t_token	*tokenp;
	t_list	*new;

	token.line = line;
	token.type = type;
	token.location.len = 0;
	token.location.start = 0;
	*iter = 0;
	while (line[*iter] != '\n' && line[*iter] != '\0')
	{
		(*iter)++;
		token.location.len++;
	}
	tokenp = malloc(sizeof(t_token));
	malloc_guard(NULL, head, NULL, tokenp);
	*tokenp = token;
	new = ft_lstnew(tokenp);
	malloc_guard(NULL, head, NULL, new);
	ft_lstadd_back(head, new);
}

void	tokenize(t_scene *scene, char *line)
{
	size_t	i;
	t_list	*head;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
			take_textures(head, line, NO, &i);
		else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
			take_textures(head, line, SO, &i);
		else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
			take_textures(head, line, WE, &i);
		else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
			take_textures(head, line, EA, &i);
		else if (line[i] == 'F' && line[i + 1] == ' ')
			take_fc(head, line, F, &i);
		else if (line[i] == 'C' && line[i + 1] == ' ')
			take_fc(head, line, C, &i);
		else
			take_map(head, line, MAP, &i);
	}
	head = scene->tokens;
}
