#include "filler.h"

void	filler(void)
{
	t_filler	filler;
	char		*line = NULL;
	t_point		new_map_size;

	gnl(STDIN_FILENO, &line);
	get_player_and_enemy(line, &filler.player, &filler.enemy);
	gnl(STDIN_FILENO, &line);
	filler.map_size = get_map_size(line);
	filler.map = get_map(filler.map_size, filler.player);

//	ft_printf_fd(STDERR_FILENO, "Player: [%c]\n", filler.player);
	print_heatmap(filler.map, filler.map_size, 0);

	while (gnl(STDIN_FILENO, &line) > -1)
	{
		if (!line)
		{
			ft_printf_fd(STDERR_FILENO, "WTF?\n");
			continue;
		}
		if (ft_strncmp(line, "Plateau", 7) == CMP_SUCCESS)
		{
			new_map_size = get_map_size(line);
			if (new_map_size.x != filler.map_size.x || new_map_size.y != filler.map_size.y)
				raise_error(ERR_INVALID_MAP_SIZE);
		}
		ft_printf_fd(STDERR_FILENO, "line: [%s]\n", line);
//		free(line);
	}
}

void	debug_launch(int argc, char **argv)
{
	t_filler	filler;

	if (argc != 2)
		ft_printf_fd(STDERR_FILENO, "GIVE ME ARGUMENTS!");
	open(argv[1], O_RDONLY);
	filler.map_size = (t_point){.x = 17, .y = 15};
	filler.map = get_map(filler.map_size, 'O');
	print_heatmap(filler.map, filler.map_size, STDOUT_FILENO);
//	ft_printf("enemy point: [%i]\n", filler.map[12][14]);
	make_heatmap(filler.map, filler.map_size, (t_point) {14, 12, 0});
	ft_printf_fd(STDOUT_FILENO, "\n-------------------------------\n");
	print_heatmap(filler.map, filler.map_size, STDOUT_FILENO);
}

int		main(int argc, char **argv)
{
	debug_launch(argc, argv);
//	filler();
	return (0);
}
