/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:51:17 by jberay            #+#    #+#             */
/*   Updated: 2024/05/29 09:55:30 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_itoa_stack(char *buf, int n)
{
	long	nbl;
	size_t	len;

	nbl = n;
	len = 1;
	while (n / 10 >= 1)
	{
		n = n / 10;
		len++;
	}
	while (len > 0)
	{
		buf[len - 1] = nbl % 10 + 48;
		nbl = nbl / 10;
		len--;
	}
}

void	get_texture_name(char *buffer, char *path, int i)
{
	char	itoa[100];

	ft_memset(buffer, 0, 100);
	ft_memset(itoa, 0, 100);
	ft_itoa_stack(itoa, i);
	ft_strlcpy(buffer, path, ft_strlen(path) + 1);
	ft_strlcat(buffer, itoa, ft_strlen(buffer) + ft_strlen(itoa) + 1);
	ft_strlcat(buffer, ".png", ft_strlen(buffer) + 5);
}
