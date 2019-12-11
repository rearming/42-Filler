#include "filler.h"

int		g_rec_call = 0;

//void	process_step(int **map, t_point map_size, t_point point, t_point step)
//{
//	if (point.x < 0 || point.x >= map_size.x || point.y < 0 || point.y >= map_size.y)
//		return ;
//	if (map[point.y][point.x] != EMPTY
//		&& map[point.y][point.x] != ENEMY
//		&& map[point.y][point.x] != PLAYER)
//		return ;
//	if (map[point.y][point.x] == EMPTY)
//		map[point.y][point.x] = point.val;
//	ft_printf("\ncall: [%i], x: [%i], y: [%i]\n", g_rec_call++, point.x, point.y);
//	print_heatmap(map, map_size, STDOUT_FILENO);
//	point.val++;
//	point.x += step.x;
//	point.y += step.y;
//	make_heatmap(map, map_size, point);
//}
//
//void	make_heatmap(int **map, t_point map_size, t_point point)
//{
//	process_step(map, map_size, point, (t_point){-1, -1});
//	process_step(map, map_size, point, (t_point){0, -1});
//	process_step(map, map_size, point, (t_point){+1, -1});
//	process_step(map, map_size, point, (t_point){-1, 0});
//	process_step(map, map_size, point, (t_point){+1, 0});
//	process_step(map, map_size, point, (t_point){-1, +1});
//	process_step(map, map_size, point, (t_point){0, +1});
//	process_step(map, map_size, point, (t_point){+1, +1});
//}

void	make_heatmap(int **map, t_point map_size, t_point point)
{
	if (point.x < 0 || point.x >= map_size.x || point.y < 0 || point.y >= map_size.y)
		return ;
	if (map[point.y][point.x] != EMPTY
		&& map[point.y][point.x] != ENEMY
		&& map[point.y][point.x] != PLAYER)
		return ;
	if (map[point.y][point.x] == EMPTY)
		map[point.y][point.x] = point.val;
	ft_printf("\ncall: [%i], x: [%i], y: [%i]\n", g_rec_call++, point.x, point.y);
	print_heatmap(map, map_size, STDOUT_FILENO);
	point.val++;
	make_heatmap(map, map_size, (t_point){point.x - 1, point.y - 1, point.val});
	make_heatmap(map, map_size, (t_point){point.x, point.y - 1, point.val});
	make_heatmap(map, map_size, (t_point){point.x + 1, point.y - 1, point.val});
	make_heatmap(map, map_size, (t_point){point.x - 1, point.y, point.val});
//	make_heatmap(map, map_size, (t_point){point.x + 1, point.y, point.val});
//	make_heatmap(map, map_size, (t_point){point.x - 1, point.y + 1, point.val});
//	make_heatmap(map, map_size, (t_point){point.x, point.y + 1, point.val});
	make_heatmap(map, map_size, (t_point){point.x + 1, point.y + 1, point.val});
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
