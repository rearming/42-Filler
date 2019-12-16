/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:29:21 by sleonard          #+#    #+#             */
/*   Updated: 2019/12/16 15:29:23 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char		**get_block_shape(t_point block_size)
{
	char	*line;
	char	**shape;
	int		y;

	shape = safe_malloc((block_size.y + 1) * sizeof(char*), raise_error);
	shape[block_size.y] = 0;
	y = 0;
	while (y < block_size.y)
	{
		gnl(INPUT_FD, &line);
		shape[y] = line;
		y++;
	}
	return (shape);
}

t_block		parse_block(void)
{
	t_block		block;
	char		*line;

	gnl(INPUT_FD, &line);
	if (ft_strncmp("Piece", line, 5) == CMP_SUCCESS)
	{
		block.size.x = ft_atoi(&line[6]);
		block.size.y = ft_atoi(&line[6 +
							ft_count_digits(block.size.x) + 1]);
		ft_swap(&block.size.x, &block.size.y);
	}
	free(line);
	block.shape = get_block_shape(block.size);
	return (block);
}
