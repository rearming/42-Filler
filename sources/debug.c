#include "filler.h"

void	print_heatmap(int **map, t_point map_size)
{
	t_cell		pos;

	pos.y = 0;
	ft_printf_fd(OUT_FD, "\n\n<------------------------------->\n");
	pos.x = 0;
	ft_printf_fd(OUT_FD, "\t");
	while (pos.x < map_size.x)
	{
		ft_printf_fd(OUT_FD, "%i\t", pos.x);
		pos.x++;
	}
	ft_printf_fd(OUT_FD, "\n");
	while (pos.y < map_size.y)
	{
		pos.x = 0;
		ft_printf_fd(OUT_FD, "%i\t", pos.y);
		while (pos.x < map_size.x)
		{
			if (map[pos.y][pos.x] == PLAYER)
				ft_printf_fd(OUT_FD, "%c\t", 'P');
			else if (map[pos.y][pos.x] == ENEMY)
				ft_printf_fd(OUT_FD, "%c\t", 'E');
			else if (map[pos.y][pos.x] == EMPTY)
				ft_printf_fd(OUT_FD, "%c\t", '.');
			else
				ft_printf_fd(OUT_FD, "%i\t", map[pos.y][pos.x]);
			pos.x++;
		}
		ft_printf_fd(OUT_FD, "\n");
		pos.y++;
	}
}

void	print_point(t_point *point, t_cell *cell)
{
	if (point)
		ft_printf_fd(OUT_FD, "x: [%i], y: [%i]\n", point->x, point->y);
	else if (cell)
		ft_printf_fd(OUT_FD, "x: [%i], y: [%i]\n", cell->x, cell->y);
	else
		ft_printf_fd(OUT_FD, "ERROR PRINTING POINT!\n");
}

void	print_block(t_block block)
{
	int		y;

	ft_printf_fd(OUT_FD, "block size ");
	print_point(&block.size, NULL);
	y = 0;
	while (block.shape[y])
	{
		ft_printf_fd(OUT_FD, "%s\n", block.shape[y]);
		y++;
	}
}
