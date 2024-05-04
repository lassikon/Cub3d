/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:26:02 by jberay            #+#    #+#             */
/*   Updated: 2024/05/02 18:26:56 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	parse_color(int *color, char *line)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	split = ft_split(line, ',');
	while (split[i])
	{
		color[j] = ft_atoi(split[i]);
		i++;
		j++;
	}
}

int	check_texture(t_scene *scene)
{
	if (scene->no_texture == NULL)
		return (0);
	if (scene->so_texture == NULL)
		return (0);
	if (scene->we_texture == NULL)
		return (0);
	if (scene->ea_texture == NULL)
		return (0);
	if (scene->floor_color[0] == -1 || scene->floor_color[1] == -1 || scene->floor_color[2] == -1)
		return (0);
	return (1);
}

void	parse_map(t_scene *scene, t_list **head)
(
	int	map_size;

	map_size = ft_lstsize(*head);
	
)

static void	call_gnl(t_scene *scene, int map_fd)
{
	t_list	*head;
	char	*line;

	head = NULL;
	scene->no_texture = NULL;
	scene->so_texture = NULL;
	scene->we_texture = NULL;
	scene->ea_texture = NULL;
	ft_memset(scene->floor_color, -1, 3);
	ft_memset(scene->ceiling_color, -1, 3);
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
		char *t_line = ((t_token *)head->content)->line;
		t_type t_type = ((t_token *)head->content)->type;
		size_t t_len = ((t_token *)head->content)->location.len - 1;
		size_t t_start = ((t_token *)head->content)->location.start;
		printf("start: %zu\n", t_start);
		printf("len: %zu\n", t_len);
		printf("value: %s\n",ft_substr(t_line, t_start, t_len));

		if (t_type == NO)
			scene->no_texture = ft_substr(t_line, t_start, t_len);
		if (t_type == SO)
			scene->so_texture = ft_substr(t_line, t_start, t_len);
		if (t_type == WE)
			scene->we_texture = ft_substr(t_line, t_start, t_len);
		if (t_type == EA)
			scene->ea_texture = ft_substr(t_line, t_start, t_len);
		if (t_type == F)
			parse_color(scene->floor_color, ft_substr(t_line, t_start, t_len));
		if (t_type == C)
			parse_color(scene->ceiling_color, ft_substr(t_line, t_start, t_len));
		if (t_type == MAP && check_texture(scene))
			parse_map(scene, &head);
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
} */

