/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janraub <janraub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:12:32 by jberay            #+#    #+#             */
/*   Updated: 2024/05/04 11:08:26 by janraub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_zero(char **map, int row, int col)
{
	if (row - 1 >= 0 && (map[row - 1][col] == '0'
		|| map[row - 1][col] == 'N' || map[row - 1][col] == 'S'
		|| map[row - 1][col] == 'W' || map[row - 1][col] == 'E'))
		map[row - 1][col] = 'V';
	if (row + 1 <= 15 && (map[row + 1][col] == '0'
		|| map[row + 1][col] == 'N' || map[row + 1][col] == 'S'
		|| map[row + 1][col] == 'W' || map[row + 1][col] == 'E'))
		map[row + 1][col] = 'V';
	if (col - 1 >= 0 && (map[row][col - 1] == '0'
		|| map[row][col - 1] == 'N' || map[row][col - 1] == 'S'
		|| map[row][col - 1] == 'W' || map[row][col - 1] == 'E'))
		map[row][col - 1] = 'V';
	if (map[row][col + 1] == '0' || map[row][col + 1] == 'N'
		|| map[row][col + 1] == 'S' || map[row][col + 1] == 'W'
		|| map[row][col + 1] == 'E')
		map[row][col + 1] = 'V';
}

static void	fill_map(char **map, int row, int col)
{
	size_t	row_max;

	row_max = ft_arrlen(map) - 1;
	if (row < 0 || col < 0 || map[row][col] == 'X')
		return ;
	map[row][col] = 'X';
	check_zero(map, row, col);
	if (row - 1 >= 0 && (map[row - 1][col] == 'J' || map[row - 1][col] == ' '))
		fill_map(map, row - 1, col);
	if (row + 1 <= (int)row_max
		&& (map[row + 1][col] == 'J' || map[row + 1][col] == ' '))
		fill_map(map, row + 1, col);
	if (col - 1 >= 0 && (map[row][col - 1] == 'J' || map[row][col - 1] == ' '))
		fill_map(map, row, col - 1);
	if (map[row][col + 1] == 'J' || map[row][col + 1] == ' ')
		fill_map(map, row, col + 1);
}

static void	is_valid_map(t_scene *scene, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	if (tmp == NULL)
		return ;
	while ((tmp)[i])
	{
		j = 0;
		while (tmp[i][j] != '\0')
		{
			if (tmp[i][j] == 'V')
			{
				free_arr(&tmp);
				error_handler(scene, FREE_SCENE, MAP_NOT_CLOSED_ERR);
			}
			j++;
		}
		i++;
	}
	free_arr(&tmp);
}

void	is_valid(t_scene *scene, size_t longest_row)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(ft_arrlen(scene->map) + 3, sizeof(char *));
	malloc_guard(scene, NULL, NULL, tmp);
	i = 0;
	tmp[i] = ft_calloc(longest_row + 3, sizeof(char));
	malloc_guard(scene, NULL, &tmp, tmp[i]);
	ft_memset(tmp[i], 'J', longest_row + 2);
	while (scene->map[i])
	{
		tmp[i + 1] = ft_calloc(longest_row + 3, sizeof(char));
		malloc_guard(scene, NULL, &tmp, tmp[i + 1]);
		ft_memset(tmp[i + 1], 'J', longest_row + 2);
		ft_memcpy(tmp[i + 1] + 1, scene->map[i], ft_strlen(scene->map[i]));
		i++;
	}
	tmp[i + 1] = ft_calloc(longest_row + 3, sizeof(char));
	malloc_guard(scene, NULL, &tmp, tmp[i + 1]);
	ft_memset(tmp[i + 1], 'J', longest_row + 2);
	tmp[i + 2] = NULL;
	fill_map(tmp, 0, 0);
	is_valid_map(scene, tmp);
}
