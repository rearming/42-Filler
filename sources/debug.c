#include "filler.h"

void		print_heatmap(int **map, t_cell map_size, int fd)
{
	t_cell		pos;

	pos.y = 0;
	ft_printf_fd(fd, "\n");
	ft_printf_fd(STDOUT_FILENO, "\n-------------------------------\n");
	while (pos.y < map_size.y)
	{
		pos.x = 0;
		while (pos.x < map_size.x)
		{
			if (map[pos.y][pos.x] == PLAYER)
				ft_printf_fd(fd, "%c\t", 'P');
			else if (map[pos.y][pos.x] == ENEMY)
				ft_printf_fd(fd, "%c\t", 'E');
			else if (map[pos.y][pos.x] == EMPTY)
				ft_printf_fd(fd, "%c\t", '.');
			else
				ft_printf_fd(fd, "%i\t", map[pos.y][pos.x]);
			pos.x++;
		}
		ft_printf_fd(fd, "\n");
		pos.y++;
	}
}
