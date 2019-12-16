/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:29:15 by sleonard          #+#    #+#             */
/*   Updated: 2019/12/16 15:29:17 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_bool		impossible(t_filler *filler, t_fuck_norme *fkn)
{
	while (fkn->check_pos.x < filler->map_size.x
		&& fkn->block_pos.x < filler->block.size.x)
	{
		if (in_shape(fkn->block_pos, filler->block.shape))
			fkn->coast += filler->map[fkn->check_pos.y][fkn->check_pos.x];
		if (is_touching(fkn->block_pos, filler->block.shape,
				filler->map[fkn->check_pos.y][fkn->check_pos.x]))
			fkn->touching++;
		if (is_enemy(fkn->block_pos, filler->block.shape,
				filler->map[fkn->check_pos.y][fkn->check_pos.x]))
			return (TRUE);
		fkn->block_pos.x++;
		fkn->check_pos.x++;
	}
	return (FALSE);
}

int			coast_of_place(t_filler *filler, t_point place_pos)
{
	t_fuck_norme	f;

	f.touching = FALSE;
	f.coast = 0;
	f.check_pos.y = place_pos.y;
	f.block_pos.y = 0;
	while (f.check_pos.y < filler->map_size.y
		&& f.block_pos.y < filler->block.size.y)
	{
		f.block_pos.x = 0;
		f.check_pos.x = place_pos.x;
		if (impossible(filler, &f))
			return (INT32_MAX);
		f.block_pos.y++;
		f.check_pos.y++;
	}
	if (f.touching == TRUE
		&& f.block_pos.x == filler->block.size.x
		&& f.block_pos.y == filler->block.size.y)
		return (f.coast - PLAYER);
	return (INT32_MAX);
}

t_point		place_block(t_filler *filler)
{
	int			best_coast;
	int			curr_coast;
	t_point		place_pos;
	t_point		best_place;

	place_pos = (t_point){0, 0};
	best_place = (t_point){-1, -1};
	best_coast = INT32_MAX;
	while (place_pos.y < filler->map_size.y)
	{
		place_pos.x = 0;
		while (place_pos.x < filler->map_size.x)
		{
			curr_coast = coast_of_place(filler, place_pos);
			if (curr_coast < best_coast)
			{
				best_coast = curr_coast;
				best_place = place_pos;
			}
			place_pos.x++;
		}
		place_pos.y++;
	}
	clean_chr_mtrx(filler->block.shape);
	return (best_place);
}
