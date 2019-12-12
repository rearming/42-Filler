#include "filler.h"

void		print_heatmap(int **map, t_point map_size, int fd)
{
	t_cell		pos;

	pos.y = 0;
	ft_printf_fd(fd, "\n\n<------------------------------->\n");
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

void	print_point(t_point *point, t_cell *cell, int fd)
{
	if (point)
		ft_printf_fd(fd, "x: [%i], y: [%i]\n", point->x, point->y);
	else if (cell)
		ft_printf_fd(fd, "x: [%i], y: [%i]\n", cell->x, cell->y);
	else
		ft_printf_fd(fd, "ERROR PRINTING POINT!\n");
}

void	print_block(t_block block, int fd)
{
	int		y;

	ft_printf_fd(fd, "block size ");
	print_point(&block.size, NULL, fd);
	ft_printf_fd(fd, "block offset ");
	print_point(&block.offset, NULL, fd);
	y = 0;
	while (block.shape[y])
	{
		ft_printf_fd(fd, "%s\n", block.shape[y]);
		y++;
	}
}
