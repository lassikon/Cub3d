/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:26:02 by jberay            #+#    #+#             */
/*   Updated: 2024/05/03 14:51:36 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	scene_syntax(t_scene *scene, t_list **head)
{
	int		flag[6];
	t_list	*tmp;

	tmp = *head;
	ft_memset(flag, 0, 6 * sizeof(int));
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == NO)
			flag[0]++;
		else if (((t_token *)tmp->content)->type == SO)
			flag[1]++;
		else if (((t_token *)tmp->content)->type == WE)
			flag[2]++;
		else if (((t_token *)tmp->content)->type == EA)
			flag[3]++;
		else if (((t_token *)tmp->content)->type == F)
			flag[4]++;
		else if (((t_token *)tmp->content)->type == C)
			flag[5]++;
		tmp = tmp->next;
	}
	if (flag[0] != 1 || flag[1] != 1 || flag[2] != 1
		|| flag[3] != 1 || flag[4] != 1 || flag[5] != 1)
	{
		free_lst(head);
		error_handler(scene, SCENE_FORMAT_ERR);
	}
}


// static void	extract_data(t_scene *scene, t_list **head)
// {
// 	size_t	longest_row;
// 	int		j;

// 	while (*head)
// 	{
// 		write_data(scene, head);
// 		if (*head)
// 			*head = (*head)->next;
// 	}
// 	if (head)
// 		free_lst(head);
// 	longest_row = 0;
// 	j = 0;
// 	while (scene->map[j])
// 	{
// 		if (ft_strlen(scene->map[j]) > longest_row)
// 			longest_row = ft_strlen(scene->map[j]);
// 		j++;
// 	}
// 	is_valid(scene, longest_row);
// }

static void	init_scene(t_scene *scene)
{
	scene->no_texture = NULL;
	scene->so_texture = NULL;
	scene->we_texture = NULL;
	scene->ea_texture = NULL;
	ft_memset(scene->floor_color, -1, 3);
	ft_memset(scene->ceiling_color, -1, 3);
	scene->map = NULL;
}

static void	call_gnl(t_scene *scene, int map_fd)
{
	t_list	*head;
	char	*line;

	head = NULL;
	while (1)
	{
		line = get_next_line(map_fd);
		if (line == NULL)
			break ;
		else if (line[0] == '\n')
			free(line);
		else if (line[0] != '\0')
			tokenize(&head, line);
	}
	scene_syntax(scene, &head);
	//extract_data(scene, &head);
	free_lst(&head);
	free_scene(scene);
}

void	check_args(t_scene *scene, int argc, char **argv)
{
	int		map_fd;

	init_scene(scene);
	if (argc != 2)
		error_handler(scene, ARG_ERR);
	if (ft_strlen(argv[1]) < 4)
		error_handler(scene, FILE_EXT_ERR);
	if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4)
		error_handler(scene, FILE_EXT_ERR);
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		error_handler(scene, FILE_OPEN_ERR);
	call_gnl(scene, map_fd);
	close(map_fd);
}
