/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:47:03 by jberay            #+#    #+#             */
/*   Updated: 2024/05/05 14:48:40 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	take_textures(t_scene *scene, char *line, t_type type, size_t *iter)
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
	malloc_guard(scene, NULL, tokenp);
	*tokenp = token;
	new = ft_lstnew(tokenp);
	malloc_guard(scene, NULL, new);
	ft_lstadd_back(&scene->tokens, new);
}

static void	take_fc(t_scene *scene, char *line, t_type type, size_t *iter)
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
	malloc_guard(scene, NULL, tokenp);
	*tokenp = token;
	new = ft_lstnew(tokenp);
	malloc_guard(scene, NULL, new);
	ft_lstadd_back(&scene->tokens, new);
}

static void	take_map(t_scene *scene, char *line, t_type type, size_t *iter)
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
	malloc_guard(scene, NULL, tokenp);
	*tokenp = token;
	new = ft_lstnew(tokenp);
	malloc_guard(scene, NULL, new);
	ft_lstadd_back(&scene->tokens, new);
}

void	tokenize(t_scene *scene, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
			take_textures(scene, line, NO, &i);
		else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
			take_textures(scene, line, SO, &i);
		else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
			take_textures(scene, line, WE, &i);
		else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
			take_textures(scene, line, EA, &i);
		else if (line[i] == 'F' && line[i + 1] == ' ')
			take_fc(scene, line, F, &i);
		else if (line[i] == 'C' && line[i + 1] == ' ')
			take_fc(scene, line, C, &i);
		else
			take_map(scene, line, MAP, &i);
	}
}
