/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:29:37 by sleonard          #+#    #+#             */
/*   Updated: 2019/12/16 15:29:38 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			**get_map(t_point map_size, char player)
{
	int		**map;
	t_cell	cell;
	char	*line;

	map = safe_malloc(map_size.y * sizeof(int*), raise_error);
	cell.y = 0;
	gnl(INPUT_FD, &line);
	free(line);
	while (cell.y < map_size.y)
	{
		map[cell.y] = safe_malloc(map_size.x * sizeof(int), raise_error);
		gnl(INPUT_FD, &line);
		fill_map_line(line, map[cell.y], player);
		free(line);
		cell.y++;
	}
	return (map);
}

t_point		get_map_size(char *line)
{
	t_point		map_size;

	map_size.x = ft_atoi(&line[7]);
	map_size.y = ft_atoi(&line[7 + ft_count_digits(map_size.x) + 1]);
	ft_swap(&map_size.x, &map_size.y);
	return (map_size);
}

void		fill_map_line(char *line, int *map_line, char player)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) || ft_isspace(line[i]))
		{
			i++;
			continue ;
		}
		if (line[i] == 'X' || line[i] == 'O')
			map_line[x] = line[i] == player ? PLAYER : ENEMY;
		else
			map_line[x] = EMPTY;
		x++;
		i++;
	}
}
