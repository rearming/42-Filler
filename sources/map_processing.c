#include "filler.h"

int		g_rec_call = -1;

static inline int is_visited(int current_value, int point_value)
{
	return (current_value == point_value + 2);
}

void		fill_around(int **map, t_point map_size, t_point center)
{
	t_point		pos;
	t_point		to_visit[8];
	int			visit_i = 0;

	pos.y = center.y - 1;
	pos.val = center.val;
	ft_printf("\ncall: [%i], x: [%i], y: [%i]\n", ++g_rec_call, center.x, center.y);
	while (pos.y <= center.y + 1 && pos.y < map_size.y)
	{
		pos.x = center.x - 1;
		while (pos.x <= center.x + 1 && pos.x < map_size.x)
		{
			if (is_visited(pos.val, map[pos.y][pos.x]) || pos.x < 0 || pos.y < 0 || (pos.x == center.x && pos.y == center.y))
			{
				pos.x++;
				continue;
			}
			if (map[pos.y][pos.x] == EMPTY)
			{
				map[pos.y][pos.x] = pos.val;
				print_heatmap(map, map_size, STDOUT_FILENO);
			}
			else if (map[pos.y][pos.x] == ENEMY)
			{
				ft_printf("ENEMY? call: [%i] x: [%i], y: [%i]\n", g_rec_call, pos.x, pos.y);
				to_visit[visit_i] = pos;
				visit_i++;
			}
			pos.x++;
		}
		pos.y++;
	}
	if (!is_visited(pos.val, map[center.y][center.x]))
	{
		map[center.y][center.x] -= 1;
		ft_printf("VISITED? call: [%i]\n", g_rec_call);
	}
	for (int i = 0; i < visit_i; i++)
	{
//		map[to_visit[i].y][to_visit[i].x] = VISITED;
		fill_around(map, map_size, to_visit[i]);
	}
}

void	make_heatmap(int **map, t_point map_size, t_point point)
{
	point.val++;

	fill_around(map, map_size, point);
}

void	fill_map_line(char *line, int *map_line, char player)
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
