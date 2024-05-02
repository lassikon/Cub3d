/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:26:02 by jberay            #+#    #+#             */
/*   Updated: 2024/05/02 15:33:27 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	call_gnl(t_scene *scene, int map_fd)
{
	t_list	*head;
	char	*line;

	head = NULL;
	scene->no_texture = NULL;
	scene->so_texture = NULL;
	scene->we_texture = NULL;
	scene->ea_texture = NULL;
	ft_bzero(scene->floor_color, 3);
	ft_bzero(scene->ceiling_color, 3);
	scene->map = NULL;
	while (1)
	{
		line = get_next_line(map_fd);
		if (line == NULL)
			break ;
		if (line != '\0')
			tokenize(&head, line);
	}
	printf("list size: %d\n", ft_lstsize(head));
	while(head)
	{
		printf("type: %d\n", ((t_token *)head->content)->type);
		printf("line: %s\n", ((t_token *)head->content)->line);
		size_t len = ((t_token *)head->content)->location.len - 1;
		size_t start = ((t_token *)head->content)->location.start;
		printf("start: %zu\n", start);
		printf("len: %zu\n", len);
		printf("value: %s\n",ft_substr((char *)((t_token *)head->content)->line, start, len));
		head = head->next;
	}
}

void	check_args(t_scene *scene, int argc, char **argv)
{
	int	map_fd;

	if (argc != 2)
		printf("Error\nWrong number of arguments\n");
	if (ft_strlen(argv[1]) < 4)
		printf("Error\nWrong file extension\n");
	if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4)
		printf("Error\nWrong file extension\n");
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		printf("Error\nCould not open file\n");
	call_gnl(scene, map_fd);
	close(map_fd);
}

