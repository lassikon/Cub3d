/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:42:54 by jberay            #+#    #+#             */
/*   Updated: 2024/05/15 08:35:39 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>

typedef enum e_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	DR,
	FL,
	CL,
	MAP
}	t_type;

typedef struct s_slice
{
	size_t	start;
	size_t	len;
}	t_slice;

typedef struct s_token
{
	t_type	type;
	t_slice	location;
	char	*line;
}	t_token;

#endif