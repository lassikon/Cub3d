/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:26:02 by jberay            #+#    #+#             */
/*   Updated: 2024/05/24 11:25:32 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	syntax_error(t_scene *scene, char *line, int *flag)
{
	int	i;
	int	invalid;

	i = 0;
	invalid = 0;
	if (flag[5] != 1 || flag[4] != 1 || flag[3] != 1
		|| flag[2] != 1 || flag[1] != 1 || flag[0] != 1)
		error_handler(scene, SCENE_FORMAT_ERR);
	if (line != NULL)
	{
		flag[7]++;
		while (line[i] && line[i] != '\n')
		{
			if (ft_strchr(MAP_CHARS, line[i]) == NULL)
				invalid = 1;
			if (ft_strchr("NSWE", line[i]) != NULL)
				flag[6]++;
			i++;
		}
		if (invalid || line[0] == '\n')
			error_handler(scene, INVALID_MAP_ERR);
	}
	if (flag[6] != 1 && line == NULL)
		error_handler(scene, INVALID_PLAYER_ERR);
}

static void	scene_syntax(t_scene *scene)
{
	int		flag[8];
	t_list	*tmp;

	tmp = scene->tokens;
	ft_memset(flag, 0, 8 * sizeof(int));
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
		else if (((t_token *)tmp->content)->type == MAP)
			syntax_error(scene, ((t_token *)tmp->content)->line, flag);
		else if (((t_token *)tmp->content)->type == NL)
			if (flag[7] > 0)
				error_handler(scene, SCENE_FORMAT_ERR);
		tmp = tmp->next;
	}
	syntax_error(scene, NULL, flag);
}

static void	init_scene(t_scene *scene)
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

static void	call_gnl(t_scene *scene, int map_fd)
{
	char	*line;
	int		i;

	line = NULL;
	while (1)
	{
		if (gnl_chk(&line, map_fd) == -1)
			error_handler(scene, MALLOC_ERR);
		if (line == NULL)
			break ;
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
			free(line);
		else
			tokenize(scene, line);
	}
	scene_syntax(scene);
	extract_data(scene);
}

void	parse(t_scene *scene, int argc, char **argv)
{
	int		map_fd;
	char	*ext;

	init_scene(scene);
	if (argc != 2)
		error_handler(scene, ARG_ERR);
	if (ft_strlen(argv[1]) < 4)
		error_handler(scene, FILE_EXT_ERR);
	ext = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (ext == NULL || ft_strlen(ext) != 4)
		error_handler(scene, FILE_EXT_ERR);
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		error_handler(scene, FILE_OPEN_ERR);
	call_gnl(scene, map_fd);
	close(map_fd);
}
