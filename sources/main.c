#include "filler.h"

static inline	t_bool	point_is_set(t_point point)
{
	return (point.x != NOT_SET && point.y != NOT_SET);
}

void	filler(void)
{
	t_filler	filler;
	char		*line = NULL;
	t_point		place_pos;

	filler.map_size = (t_point){NOT_SET, NOT_SET};

	gnl(INPUT_FD, &line);
	get_player_and_enemy(line, &filler.player, &filler.enemy);

	while ((gnl(STDIN_FILENO, &line)) > -1)
	{
		if (!line)
			exit(42);
		if (ft_strncmp(line, "Plateau", 7) == CMP_SUCCESS)
		{
			if (!point_is_set(filler.map_size))
				filler.map_size = get_map_size(line);
			filler.map = get_map(filler.map_size, filler.player);
			make_heatmap(filler.map, filler.map_size, ENEMY);
			place_pos = place_block(filler.map, filler.map_size, parse_block());
			ft_printf_fd(STDOUT_FILENO, "%i %i\n", place_pos.y, place_pos.x);
			if (!point_is_set(place_pos))
				exit(21);
			free_map(filler.map, filler.map_size);
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

	close(INPUT_FD);
	open(argv[2], O_RDONLY);

	block = parse_block();

	place = place_block(filler.map, filler.map_size, block);

	print_heatmap(filler.map, filler.map_size);

	free_map(filler.map, filler.map_size);
	clean_chr_mtrx(block.shape);
}

int		main(int argc, char **argv)
{
//	debug_launch(argc, argv);
	filler();
	return (0);
}
