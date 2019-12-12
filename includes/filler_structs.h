#ifndef FILLER_STRUCTS_H
# define FILLER_STRUCTS_H

#include "libft.h"

typedef struct		s_cell
{
	int				x;
	int				y;
	int				value;
}					t_cell;

typedef struct		s_filler
{
	char			player;
	char			enemy;
	t_cell			map_size;
	int				**map;
}					t_filler;

#endif
