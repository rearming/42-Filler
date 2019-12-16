/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:29:41 by sleonard          #+#    #+#             */
/*   Updated: 2019/12/16 15:29:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_bool	cell_is_valid(t_cell pos, t_cell central_point, int *out_pos_x)
{
	t_bool	is_valid;

	is_valid = !(pos.y < 0 || pos.x < 0
			|| (pos.x == central_point.x && pos.y == central_point.y));
	if (!is_valid)
		(*out_pos_x)++;
	return (is_valid);
}

void	fill_around(
		int **map,
		t_point map_size,
		t_cell central_point,
		int center_value)
{
	t_cell		pos;
	t_cell		cells_to_visit[8];
	int			cell_i;

	cell_i = 0;
	pos.y = central_point.y - 1;
	pos.value = central_point.value;
	while (pos.y <= central_point.y + 1 && pos.y < map_size.y)
	{
		pos.x = central_point.x - 1;
		while (pos.x <= central_point.x + 1 && pos.x < map_size.x)
		{
			if (!cell_is_valid(pos, central_point, &pos.x))
				continue ;
			if (map[pos.y][pos.x] == EMPTY)
				map[pos.y][pos.x] = pos.value;
			else if (map[pos.y][pos.x] == center_value)
			{
				cells_to_visit[cell_i] = pos;
				cell_i++;
			}
			pos.x++;
		}
		pos.y++;
	}
}

int		count_starts(int **map, t_point map_size, int value_to_find)
{
	int		x;
	int		y;
	int		starts;

	y = 0;
	starts = 0;
	while (y < map_size.y)
	{
		x = 0;
		while (x < map_size.x)
		{
			if (map[y][x] == value_to_find)
				starts++;
			x++;
		}
		y++;
	}
	return (starts);
}

t_cell	*find_starts(int **map,
					t_point map_size,
					int value_to_find,
					int *out_starts_num)
{
	t_point		pos;
	int			start_num;
	t_cell		*starts;

	start_num = 0;
	*out_starts_num = count_starts(map, map_size, value_to_find);
	if (*out_starts_num == 0)
		return (NULL);
	starts = safe_malloc(*out_starts_num * sizeof(t_cell), raise_error);
	pos.y = 0;
	while (pos.y < map_size.y)
	{
		pos.x = 0;
		while (pos.x < map_size.x)
		{
			if (map[pos.y][pos.x] == value_to_find)
			{
				starts[start_num] = (t_cell){pos.x, pos.y, value_to_find + 1};
				start_num++;
			}
			pos.x++;
		}
		pos.y++;
	}
	return (starts);
}

void	make_heatmap(int **map, t_point map_size, int center_value)
{
	int			i;
	int			starts_num;
	t_cell		*starts;

	while (21)
	{
		starts_num = 0;
		starts = find_starts(map, map_size, center_value++, &starts_num);
		if (!starts)
			break ;
		i = 0;
		while (i < starts_num)
		{
			fill_around(map, map_size,
					(t_cell){starts[i].x, starts[i].y, starts[0].value},
					starts[0].value - 1);
			i++;
		}
		free(starts);
	}
}
