/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:23:09 by sleonard          #+#    #+#             */
/*   Updated: 2019/12/16 15:23:11 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_STRUCTS_H
# define FILLER_STRUCTS_H

# include "libft.h"

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

typedef struct		s_fuck_norme
{
	t_point			check_pos;
	t_point			block_pos;
	int				coast;
	t_bool			touching;
}					t_fuck_norme;

typedef struct		s_filler
{
	char			player;
	char			enemy;
	t_point			map_size;
	t_block			block;
	int				**map;
}					t_filler;

#endif
