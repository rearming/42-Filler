#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "filler_defines.h"
# include "filler_structs.h"

/*
**	parsing
*/

int			**get_map(t_point map_size, char player);
t_point		get_map_size(char *line);
void		get_player_and_enemy(char *line, char *out_player, char *out_enemy);

/*
**	map processing
*/

void fill_map_line(char *line, int *map_line, char player);
void	make_heatmap(int **map, t_point map_size, t_point point);

/*
**	utils
*/

void	raise_error(int err_code);
void	*safe_malloc(size_t size, void (*exit_func)(int), int err_code);
void	print_heatmap(int **map, t_point map_size, int fd);

#endif
