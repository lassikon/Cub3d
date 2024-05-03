/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:12:32 by jberay            #+#    #+#             */
/*   Updated: 2024/05/03 13:42:22 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_zero(char **map, int row, int col)
{
	if (row - 1 >= 0 && map[row - 1][col] == '0')
		return (1);
	if (row + 1 <= 15 && map[row + 1][col] == '0')
		return (1);
	if (col - 1 >= 0 && map[row][col - 1] == '0')
		return (1);
	if (map[row][col + 1] == '0')
		return (1);
	return (0);
}

static void	fill_map(char **map, int row, int col, size_t row_max)
{
	if (row < 0 || col < 0 || map[row][col] == 'X')
		return ;
	map[row][col] = 'X';
	if (check_zero(map, row, col))
	{
		printf("Error\nMap is not closed\n");
		exit(1);
	}
	if (row - 1 >= 0 && (map[row - 1][col] == 'J' || map[row - 1][col] == ' '))
		fill_map(map, row - 1, col, row_max);
	if (row + 1 <= (int)row_max && (map[row + 1][col] == 'J' || map[row + 1][col] == ' '))
		fill_map(map, row + 1, col, row_max);
	if (col - 1 >= 0 && (map[row][col - 1] == 'J' || map[row][col - 1] == ' '))
		fill_map(map, row, col - 1, row_max);
	if (map[row][col + 1] == 'J' || map[row][col + 1] == ' ')
		fill_map(map, row, col + 1, row_max);
}

void	is_valid(t_scene *scene, size_t longest_row)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(ft_arrlen(scene->map) + 3, sizeof(char *));
	malloc_guard_scene(scene, NULL, NULL, tmp);
	i = 0;
	tmp[i] = ft_calloc(longest_row + 3, sizeof(char));
	malloc_guard_scene(scene, NULL, &tmp, tmp[i]);
	ft_memset(tmp[i], 'J', longest_row + 2);
	while (scene->map[i])
	{
		tmp[i + 1] = ft_calloc(longest_row + 3, sizeof(char));
		malloc_guard_scene(scene, NULL, &tmp, tmp[i + 1]);
		ft_memset(tmp[i + 1], 'J', longest_row + 2);
		ft_memcpy(tmp[i + 1] + 1, scene->map[i], ft_strlen(scene->map[i]));
		i++;
	}
	tmp[i + 1] = ft_calloc(longest_row + 3, sizeof(char));
	malloc_guard_scene(scene, NULL, &tmp, tmp[i + 1]);
	ft_memset(tmp[i + 1], 'J', longest_row + 2);
	tmp[i + 2] = NULL;
	fill_map(tmp, 0, 0, ft_arrlen(tmp) - 1);
	free_arr(&tmp);
}
