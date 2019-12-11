#include "filler.h"

int		**get_map(t_point map_size, char player)
{
	int		**map;
	t_point	cell;
	char	*line = NULL;

	map = safe_malloc(map_size.y * sizeof(int*), raise_error, ERR_MALLOC);
	cell.y = 0;
	gnl(3, &line);
	free(line);
	while (cell.y < map_size.y)
	{
		map[cell.y] = safe_malloc(map_size.x * sizeof(int), raise_error, ERR_MALLOC);
		gnl(3, &line);
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

void		get_player_and_enemy(char *line, char *out_player, char *out_enemy)
{
	if ((ft_strncmp("$$$ exec p", line, 10)) != CMP_SUCCESS)
		raise_error(ERR_INVALID_INIT_STR);
	if (line[10] == '1')
	{
		*out_player = 'O';
		*out_enemy = 'X';
	}
	else if (line[10] == '2')
	{
		*out_player = 'X';
		*out_enemy = 'O';
	}
	else
		raise_error(ERR_INVALID_PLAYER_NUMBER);
}
