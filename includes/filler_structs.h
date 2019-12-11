#ifndef FILLER_STRUCTS_H
# define FILLER_STRUCTS_H

#include "libft.h"

typedef struct		s_point
{
	int				x;
	int				y;
	int				val;
}					t_point;

typedef struct		s_filler
{
	char			player;
	char			enemy;
	t_point			map_size;
	int				**map;
}					t_filler;

#endif
