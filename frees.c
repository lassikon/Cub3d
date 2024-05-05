/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:35:07 by jberay            #+#    #+#             */
/*   Updated: 2024/05/05 13:49:13 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_funcs(t_scene *scene, t_list **head, char ***tmp, void *ptr)
{
	if (scene != NULL)
	{
		free_scene(scene);
		free(scene);
	}
	if (head != NULL)
	{
		free_lst(head);
		free(head);
	}
	if (tmp != NULL)
	{
		free_arr(tmp);
		free(tmp);
	}
	if (ptr != NULL)
	{
		free(ptr);
	}
}

void	free_arr(char ***array)
{
	size_t	i;
	char	**tmp;

	if (*array == NULL)
		return ;
	tmp = *array;
	i = 0;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	*array = NULL;
}

void	free_lst(t_list **head)
{
	t_list	*tmp;

	if (*head == NULL)
		return ;
	tmp = *head;
	while (tmp)
	{
		free((char *)((t_token *)(tmp)->content)->line);
		((t_token *)(tmp)->content)->line = NULL;
		tmp = tmp->next;
	}
	ft_lstclear(head, free);
}

void	free_scene(t_scene *scene)
{
	if (scene->no_texture != NULL)
	{
		free(scene->no_texture);
		scene->no_texture = NULL;
	}
	if (scene->so_texture != NULL)
	{
		free(scene->so_texture);
		scene->so_texture = NULL;
	}
	if (scene->we_texture != NULL)
	{
		free(scene->we_texture);
		scene->we_texture = NULL;
	}
	if (scene->ea_texture != NULL)
	{
		free(scene->ea_texture);
		scene->ea_texture = NULL;
	}
	if (scene->map != NULL)
	{
		free_arr(&(scene->map));
		scene->map = NULL;
	}
	if (scene->tokens != NULL)
	{
		free_lst(&(scene->tokens));
		scene->tokens = NULL;
	}
}
