#ifndef FILLER_STRUCTS_H
# define FILLER_STRUCTS_H

#include "libft.h"

typedef int			t_bool;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_cell
{
	int				x;
	int				y;
	int				value;
}					t_cell;

typedef struct		s_block
{
	char			**shape;
	t_point			size;
}					t_block;

typedef struct		s_filler
{
	char			player;
	char			enemy;
	t_point			map_size;
	int				**map;
}					t_filler;

#endif
