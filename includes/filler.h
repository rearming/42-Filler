/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:22:52 by sleonard          #+#    #+#             */
/*   Updated: 2019/12/16 15:22:53 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "filler_defines.h"
# include "filler_structs.h"

# include <fcntl.h>
# include <stdint.h>

/*
**	parsing
*/

int			**get_map(t_point map_size, char player);
t_point		get_map_size(char *line);
void		get_player_and_enemy(char *line, char *out_player, char *out_enemy);
t_block		parse_block(void);

/*
**	map processing
*/

void		fill_map_line(char *line, int *map_line, char player);
void		make_heatmap(int **map, t_point map_size, int center_value);

/*
**	algo
*/

t_point		place_block(t_filler *filler);
int			coast_of_place(t_filler *filler, t_point place_pos);
/*
**	utils
*/

void		raise_error(int err_code);
void		*safe_malloc(size_t size, void (*exit_func)(int));
void		free_map(int **map, t_point map_size);

t_bool		in_shape(t_point block_pos, char **shape);
t_bool		is_touching(t_point block_pos, char **shape, int cell);
t_bool		is_enemy(t_point block_pos, char **shape, int cell);
t_bool		point_is_set(t_point point);

/*
**	debug
*/
void		print_heatmap(int **map, t_point map_size);
void		print_block(t_block block);
void		print_point(t_point *point, t_cell *cell);
t_block		get_block(void);

#endif
