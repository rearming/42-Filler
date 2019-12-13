#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "filler_defines.h"
# include "filler_structs.h"
# include <fcntl.h>

int gnl2(int fd, char **line);

/*
**	parsing
*/

int 		**get_map(t_point map_size, char player);
t_point 	get_map_size(char *line);
void		get_player_and_enemy(char *line, char *out_player, char *out_enemy);

t_block		parse_block(void);

/*
**	map processing
*/

void 		fill_map_line(char *line, int *map_line, char player);
void 		make_heatmap(int **map, t_point map_size, int center_value);

/*
**	algo
*/

t_point		place_block(int **map, t_point map_size, t_block block);
int			coast_of_place(int **map, t_point map_size,
						  t_block block, t_point place_pos);
/*
**	utils
*/

void		raise_error(int err_code);
void		*safe_malloc(size_t size, void (*exit_func)(int));
void		free_map(int **map, t_point map_size);

/*
**	debug
*/
void print_heatmap(int **map, t_point map_size);
void print_block(t_block block);
void print_point(t_point *point, t_cell *cell);
t_block		get_block(void);

#endif
