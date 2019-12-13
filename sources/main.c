#include "filler.h"

static inline	t_bool	point_is_set(t_point point)
{
	return (point.x != NOT_SET && point.y != NOT_SET);
}

void	filler(void)
{
	t_filler	filler;
	char		*line = NULL;
	t_point		new_map_size;
	t_point		place_pos;

	filler.map_size = (t_point){NOT_SET, NOT_SET};

	gnl(INPUT_FD, &line);
	get_player_and_enemy(line, &filler.player, &filler.enemy);

	while ((gnl(STDIN_FILENO, &line)) > -1)
	{
		if (!line)
			exit(1);
		if (ft_strncmp(line, "Plateau", 7) == CMP_SUCCESS)
		{
			if (!point_is_set(filler.map_size))
				filler.map_size = get_map_size(line);
			else
			{
				new_map_size = get_map_size(line);
				if (new_map_size.x != filler.map_size.x || new_map_size.y != filler.map_size.y)
					raise_error(ERR_INVALID_MAP_SIZE);
			}
			filler.map = get_map(filler.map_size, filler.player);
			make_heatmap(filler.map, filler.map_size, ENEMY);
			place_pos = place_block(filler.map, filler.map_size, parse_block());
			if (point_is_set(place_pos))
			{
				ft_printf_fd(STDOUT_FILENO, "%i %i\n", place_pos.y, place_pos.x);
			}
			else
			{
				ft_printf_fd(STDOUT_FILENO, "%i %i\n", place_pos.y, place_pos.x);
				exit(1);
			}
		}
		free(line);
	}
}

void	debug_launch(int argc, char **argv)
{
	t_filler	filler;
	t_block		block;
	t_point		place;

	if (argc != 3)
		ft_printf_fd(STDERR_FILENO, "GIVE ME ARGUMENTS!");

	open(argv[1], O_RDONLY);
	filler.map_size = (t_point){.x = 17, .y = 15};
	filler.map = get_map(filler.map_size, 'O');

	make_heatmap(filler.map, filler.map_size, ENEMY);
	print_heatmap(filler.map, filler.map_size);

	close(INPUT_FD);
	open(argv[2], O_RDONLY);

	block = parse_block();
	print_block(block);
	place = place_block(filler.map, filler.map_size, parse_block());

	print_heatmap(filler.map, filler.map_size);

//	free_map(filler.map, filler.map_size);
}

int		main(int argc, char **argv)
{
	debug_launch(argc, argv);
//	filler();
	return (0);
}
