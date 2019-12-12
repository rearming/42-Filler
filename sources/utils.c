#include "filler.h"

void	free_map(int **map, t_point map_size)
{
	int i;

	i = 0;
	while (i < map_size.y)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
