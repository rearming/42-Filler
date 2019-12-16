/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:29:32 by sleonard          #+#    #+#             */
/*   Updated: 2019/12/16 15:29:33 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	filler_loop(t_filler *filler, char *line)
{
	t_point		place_pos;

	if (!line)
		exit(42);
	if (ft_strncmp(line, "Plateau", 7) == CMP_SUCCESS)
	{
		if (!point_is_set(filler->map_size))
			filler->map_size = get_map_size(line);
		filler->map = get_map(filler->map_size, filler->player);
		make_heatmap(filler->map, filler->map_size, ENEMY);
		filler->block = parse_block();
		place_pos = place_block(filler);
		ft_printf_fd(STDOUT_FILENO, "%i %i\n", place_pos.y, place_pos.x);
		if (!point_is_set(place_pos))
			exit(21);
		free_map(filler->map, filler->map_size);
	}
}

int		main(void)
{
	t_filler	filler;
	char		*line;

	filler.map_size = (t_point){NOT_SET, NOT_SET};
	gnl(INPUT_FD, &line);
	get_player_and_enemy(line, &filler.player, &filler.enemy);
	free(line);
	while ((gnl(STDIN_FILENO, &line)) > -1)
	{
		filler_loop(&filler, line);
		free(line);
	}
	return (0);
}
