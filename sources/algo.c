#include "filler.h"

//todo correct size of block (by shape)

static inline t_bool in_shape(t_point block_pos, char **shape)
{
	return (shape[block_pos.y][block_pos.x] == SHAPE_CHAR);
}

static inline t_bool is_touching(t_point block_pos, char **shape, int cell)
{
	return (in_shape(block_pos, shape) && cell == PLAYER);
}

static inline t_bool is_enemy(t_point block_pos, char **shape, int cell)
{
	return (in_shape(block_pos, shape) && cell == ENEMY);
}

int		coast_of_place(int **map, t_point map_size, t_block block, t_point place_pos)
{
	t_point		check_pos;
	t_point		block_pos;
	int			coast;
	t_bool		touching;

	touching = FALSE;
	coast = 0;
	check_pos.y = place_pos.y;
	block_pos.y = 0;
	while (check_pos.y < map_size.y && block_pos.y < block.size.y)
	{
		block_pos.x = 0;
		check_pos.x = place_pos.x;
		while (check_pos.x < map_size.x && block_pos.x < block.size.x)
		{
			if (in_shape(block_pos, block.shape))
				coast += map[check_pos.y][check_pos.x];
			if (is_touching(block_pos, block.shape, map[check_pos.y][check_pos.x])) //todo может нужна более сложная проверка
				touching++;
			if (is_enemy(block_pos, block.shape, map[check_pos.y][check_pos.x]))
				return (INT32_MAX);
			block_pos.x++;
			check_pos.x++;
		}
		block_pos.y++;
		check_pos.y++;
	}
	if (touching == TRUE && block_pos.x == block.size.x && block_pos.y == block.size.y)
		return (coast - PLAYER);
	return (INT32_MAX);
}

t_point		place_block(int **map, t_point map_size, t_block block)
{
	int			best_coast;
	int			curr_coast;
	t_point		place_pos;
	t_point		best_place;
	
	place_pos = (t_point){0, 0};
	best_place = (t_point){-1, -1};
	best_coast = INT32_MAX;
	while (place_pos.y < map_size.y)
	{
		place_pos.x = 0;
		while (place_pos.x < map_size.x)
		{
			curr_coast = coast_of_place(map, map_size, block, place_pos);
			if (curr_coast < best_coast)
			{
				best_coast = curr_coast;
				best_place = place_pos;
			}
			place_pos.x++;
		}
		place_pos.y++;
	}
	ft_printf_fd(OUT_FD, "best_coast of place: [%i]\n", best_coast);
	ft_printf_fd(OUT_FD, "best_place x: [%i], y: [%i]\n", best_place.x, best_place.y);
//	print_heatmap(map, map_size);
	return (best_place);
}
