/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_chk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 08:37:53 by jberay            #+#    #+#             */
/*   Updated: 2024/05/16 10:12:33 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	on_error(char **gnl)
{
	free (*gnl);
	*gnl = 0;
	return (-1);
}

static int	get_line(char **gnl, char **line)
{
	int		i;
	char	*tmp;
	char	*new;

	i = 0;
	tmp = *gnl;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	*line = ft_substr(tmp, 0, i);
	if (!*line)
		return (on_error(gnl));
	new = ft_substr(tmp, i, ft_strlen(tmp) - i);
	if (!new)
	{
		free (*line);
		*line = 0;
		return (on_error(gnl));
	}
	free (tmp);
	*gnl = new;
	return (0);
}

static int	ft_call_read(int fd, char **gnl)
{
	char	*buf;
	char	*temp;
	int		read_strlen;

	temp = *gnl;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	read_strlen = read(fd, buf, BUFFER_SIZE);
	if (read_strlen < 0)
	{
		free (buf);
		return (-1);
	}
	buf[read_strlen] = '\0';
	*gnl = ft_strjoin(temp, buf);
	if (!*gnl)
	{
		free (temp);
		free (buf);
		return (-1);
	}
	free(temp);
	free(buf);
	return (read_strlen);
}

int	gnl_chk(char **line, int fd)
{
	static char	*gnl;
	int			read_strlen;

	if (!gnl)
	{
		gnl = malloc(1);
		if (!gnl)
			return (-1);
		gnl[0] = '\0';
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &gnl, 0) < 0)
		return (on_error(&gnl));
	read_strlen = ft_call_read(fd, &gnl);
	while (ft_strchr(gnl, '\n') == 0 && read_strlen > 0)
		read_strlen = ft_call_read(fd, &gnl);
	if (read_strlen < 0)
		return (on_error(&gnl));
	if (*gnl == '\0')
	{
		free(gnl);
		gnl = 0;
		*line = NULL;
		return (0);
	}
	return (get_line(&gnl, line));
}
