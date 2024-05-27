/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:47:03 by jberay            #+#    #+#             */
/*   Updated: 2024/05/27 14:38:12 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_type	get_type(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (NO);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (SO);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (WE);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (EA);
	else if (ft_strncmp(line, "F", 1) == 0)
		return (F);
	else if (ft_strncmp(line, "C", 1) == 0)
		return (C);
	else
		return (MAP);
}

static void	take_textures(t_scene *scene, char *line, size_t *iter)
{
	t_token	token;
	t_token	*tokenp;
	t_list	*new;

	token.line = line;
	token.type = get_type(&line[*iter]);
	*iter += 2;
	while (line[*iter] == ' ')
		*iter += 1;
	token.location.start = *iter;
	token.location.len = 0;
	while (line[*iter] != '\n' && line[*iter] != '\0')
	{
		(*iter)++;
		token.location.len++;
	}
	if (line[*iter] == '\n')
		(*iter)++;
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
	if (line[*iter] == '\n')
		(*iter)++;
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
	if (line[*iter] == '\n')
		(*iter)++;
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
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (ft_strncmp(&line[i], "NO ", 3) == 0
			|| ft_strncmp(&line[i], "SO ", 3) == 0
			|| ft_strncmp(&line[i], "WE ", 3) == 0
			|| ft_strncmp(&line[i], "EA ", 3) == 0)
			take_textures(scene, line, &i);
		else if (ft_strncmp(&line[i], "F ", 2) == 0)
			take_fc(scene, line, F, &i);
		else if (ft_strncmp(&line[i], "C ", 2) == 0)
			take_fc(scene, line, C, &i);
		else if (line[0] == '\n')
			take_map(scene, line, NL, &i);
		else
			take_map(scene, line, MAP, &i);
	}
}
