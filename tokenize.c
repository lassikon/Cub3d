/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:47:03 by jberay            #+#    #+#             */
/*   Updated: 2024/05/02 18:27:07 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	take_textures(t_list **head, char *line, t_type type, size_t *iter)
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
	while (line[*iter])
	{
		(*iter)++;
		token.location.len++;
	}
	tokenp = malloc(sizeof(t_token));
	malloc_guard(head, tokenp);
	*tokenp = token;
	new = ft_lstnew(tokenp);
	malloc_guard(head, new);
	ft_lstadd_back(head, new);
}

void	take_fc(t_list **head, char *line, t_type type, size_t *iter)
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
	while (line[*iter])
	{
		(*iter)++;
		token.location.len++;
	}
	tokenp = malloc(sizeof(t_token));
	malloc_guard(head, tokenp);
	*tokenp = token;
	new = ft_lstnew(tokenp);
	malloc_guard(head, new);
	ft_lstadd_back(head, new);
}

void	take_map(t_list **head, char *line, t_type type, size_t *iter)
{
	t_token	token;
	t_token	*tokenp;
	t_list	*new;

	token.line = line;
	token.type = type;
	token.location.len = 0;
	while (line[*iter])
	{
		(*iter)++;
		token.location.len++;
	}
	tokenp = malloc(sizeof(t_token));
	malloc_guard(head, tokenp);
	*tokenp = token;
	new = ft_lstnew(tokenp);
	malloc_guard(head, new);
	ft_lstadd_back(head, new);
}

void	tokenize(t_list	**head, char *line)
{
	size_t	iter;

	iter = 0;
	while (line[iter] != '\0')
	{
		if (line[iter] == 'N' && line[iter + 1] == 'O')
			take_textures(head, line, NO, &iter);
		else if (line[iter] == 'S' && line[iter + 1] == 'O')
			take_textures(head, line, SO, &iter);
		else if (line[iter] == 'W' && line[iter + 1] == 'E')
			take_textures(head, line, WE, &iter);
		else if (line[iter] == 'E' && line[iter + 1] == 'A')
			take_textures(head, line, EA, &iter);
		else if (line[iter] == 'F')
			take_fc(head, line, F, &iter);
		else if (line[iter] == 'C')
			take_fc(head, line, C, &iter);
		else if (line[iter] == ' ' || line[iter] == '\t' || line[iter] == '\n')
			iter++;
		else
			take_map(head, line, MAP, &iter);
	}
}

void	malloc_guard(t_list **head, void *ptr)
{
	if (ptr == NULL)
	{
		ft_lstclear(head, free);
		printf("Malloc failed");
		exit(1);
	}
} */
