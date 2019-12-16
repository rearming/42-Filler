/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:29:56 by sleonard          #+#    #+#             */
/*   Updated: 2019/12/16 15:29:57 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			free_map(int **map, t_point map_size)
{
	int i;

	i = 0;
	while (i < map_size.y)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

inline t_bool	in_shape(t_point block_pos, char **shape)
{
	return (shape[block_pos.y][block_pos.x] == SHAPE_CHAR);
}

inline t_bool	is_touching(t_point block_pos, char **shape, int cell)
{
	return (in_shape(block_pos, shape) && cell == PLAYER);
}

inline t_bool	is_enemy(t_point block_pos, char **shape, int cell)
{
	return (in_shape(block_pos, shape) && cell == ENEMY);
}

inline t_bool	point_is_set(t_point point)
{
	return (point.x != NOT_SET && point.y != NOT_SET);
}
