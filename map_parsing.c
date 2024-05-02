/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:26:02 by jberay            #+#    #+#             */
/*   Updated: 2024/05/02 22:03:49 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		printf("env[%zu]:%s\n", i, array[i]);
		i++;
	}
}

void	ft_freearr(char ***array)
{
	size_t	i;
	char	**tmp;

	tmp = *array;
	i = 0;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	*array = NULL;
}


int	ft_arrdup(char ***dst_add, char **src)
{
	size_t	src_size;
	size_t	i;
	char	**dst;

	if (!src)
		return (1);
	src_size = ft_arrlen(src);
	dst = ft_calloc(src_size + 1, sizeof(char *));
	if (!dst)
		return (1);
	i = 0;
	while (i < src_size)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			ft_freearr(&dst);
			return (1);
		}
		i++;
	}
	dst[i] = NULL;
	*dst_add = dst;
	return (0);
}

void	parse_color(int *color, char *line)
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
{
	int		map_size;
	size_t	i = 0;
	
	map_size = ft_lstsize(*head);
	printf("%d\n", map_size);
	scene->map = ft_calloc(map_size, sizeof(char *));
	if (!scene->map)
		printf("Error\nCould not allocate memory\n");
	t_list *tmp = *head;
	size_t t_longest = 0;
	while(tmp)
	{
		if (((t_token *)tmp->content)->location.len > t_longest)
			t_longest = ((t_token *)tmp->content)->location.len;
		tmp = tmp->next;
	}
	printf("longest: %zu\n", t_longest);
	while (*head)
	{
		char *t_line = ((t_token *)(*head)->content)->line;
		t_type t_type = ((t_token *)(*head)->content)->type;
		size_t t_len = ((t_token *)(*head)->content)->location.len;
		size_t t_start = ((t_token *)(*head)->content)->location.start;
		if (t_type == MAP)
		{
			scene->map[i] = ft_calloc(t_longest, sizeof(char));
			if (!scene->map[i])
				printf("Error\nCould not allocate memory\n");
			ft_memset(scene->map[i], 0, t_longest);
			ft_memmove(scene->map[i], t_line + t_start, t_len);
			printf("map: %s\n", scene->map[i]);
		}
		*head = (*head)->next;
		i++;
	}
}

int	find_char(char **map, int *pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 31)
			{
				pos[0] = j;
				pos[1] = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


void	fill_map(char **map, int y, int x)
{
	if (y < 0 || x < 0 || map[y][x] == 'X')
		return ;
	if (map[y][x] == '0')
	{
		printf("not surounded\n");
		return ;
	}
	map[y][x] = 'X';
	if (y - 1 >= 0 && map[y - 1][x] == 31)
	{
		printf("1x: %d, y: %d\n", x, y);
		fill_map(map, y - 1, x);
	}
	if (y + 1 <= 13 && map[y + 1][x] == 31)
	{
		printf("2x: %d, y: %d\n", x, y);
		fill_map(map, y + 1, x);
	}
	if (x - 1 >= 0 && map[y][x - 1] == 31)
	{
		printf("3x: %d, y: %d\n", x, y);
		fill_map(map, y, x - 1);
	}
	if (map[y][x + 1] == 31)
	{
		printf("4x: %d, y: %d\n", x, y);
		fill_map(map, y, x + 1);
	}
}

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
		if (line[0] != '\0')
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
		if (head)
			head = head->next;
	}
	char **tmp;
	tmp = ft_calloc(ft_arrlen(scene->map) + 3, sizeof(char *));
	int i = 0;
	
	tmp[i] = ft_calloc(ft_strlen(scene->map[i]) + 3, sizeof(char));
	ft_memset(tmp[i], 'J', ft_strlen(scene->map[i]) + 3);
	ft_memmove(tmp[i] + 1, scene->map[i], ft_strlen(scene->map[i]) + 1);
	while (scene->map[i])
	{
		tmp[i + 1] = ft_calloc(ft_strlen(scene->map[i]) + 3, sizeof(char));
		ft_memset(tmp[i + 1], 'J', ft_strlen(scene->map[i]) + 3);
		ft_memmove(tmp[i + 1] + 1, scene->map[i], ft_strlen(scene->map[i]) + 1);
		i++;
	}
	
	/* tmp[i + 1] = ft_calloc(ft_strlen(scene->map[i]) + 3, sizeof(char));
	ft_memset(tmp[i + 1], 'J', ft_strlen(scene->map[i]) + 3);
	ft_memmove(tmp[i + 1] + 1, scene->map[i], ft_strlen(scene->map[i]) + 1); */
	printf("here\n");
	int pos[2];
	print_array(tmp);
	find_char(tmp, pos);
	fill_map(tmp, pos[1], pos[0]);
	print_array(tmp);
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
