#include "filler.h"

void		fill_around(int **map, t_point map_size, t_cell center, int center_value)
{
	t_cell		pos;
	t_cell		cells_to_visit[8];
	int			cell_i;

	cell_i = 0;
	pos.y = center.y - 1;
	pos.value = center.value;
	while (pos.y <= center.y + 1 && pos.y < map_size.y)
	{
		pos.x = center.x - 1;
		while (pos.x <= center.x + 1 && pos.x < map_size.x)
		{
			if (pos.y < 0 || pos.x < 0)
			{
				pos.x++;
				continue ;
			}
			if (pos.x == center.x && pos.y == center.y)
			{
				pos.x++;
				continue ;
			}
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

t_cell		*find_starts(int **map,
					t_point map_size,
					int value_to_find,
					int *out_starts_num)
{
	int			x;
	int			y;
	int			start_num = 0;
	t_cell		*starts;

	*out_starts_num = count_starts(map, map_size, value_to_find);
	starts = safe_malloc(*out_starts_num * sizeof(t_cell), raise_error);
	y = 0;
	while (y < map_size.y)
	{
		x = 0;
		while (x < map_size.x)
		{
			if (map[y][x] == value_to_find)
			{
				starts[start_num] = (t_cell){x, y, value_to_find + 1};
				start_num++;
			}
			x++;
		}
		y++;
	}
	if (start_num)
		return (starts);
	return (NULL);
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
		ft_printf_fd(OUT_FD, "starts num: [%i]\n", starts_num);
		if (!starts)
			break ;
		i = 0;
		while (i < starts_num)
		{
			fill_around(map, map_size,
					(t_cell){starts[i].x, starts[i].y, starts[0].value}, starts[0].value - 1);
			i++;
		}
		free(starts);
	}
}
