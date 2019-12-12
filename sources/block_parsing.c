#include "filler.h"

t_block		get_block(void)
{
	t_block		block;

	block.size.x = 2;
	block.size.y = 4;

//	block.offset = //todo offsets

	block.shape = safe_malloc((block.size.y + 1) * sizeof(char*), raise_error);
	block.shape[block.size.y] = 0;
	block.shape[0] = ft_strdup(".*");
	block.shape[1] = ft_strdup(".*");
	block.shape[2] = ft_strdup(".*");
	block.shape[3] = ft_strdup("**");
	return (block);
}

char		**get_block_shape(t_point block_size)
{
	char	*line;
	char	**shape;
	int		y;

	shape = safe_malloc((block_size.y + 1) * sizeof(char*), raise_error);
	shape[block_size.y] = 0;
	y = 0;
	while (y < block_size.y)
	{
		gnl(FD, &line);
		shape[y] = line;
		y++;
	}
	return (shape);
}

t_block		parse_block(void)
{
	t_block block;
	char *line;

	gnl(FD, &line);
	if (ft_strncmp("Piece", line, 5) == CMP_SUCCESS)
	{
		block.size.x = ft_atoi(&line[6]);
		block.size.y = ft_atoi(&line[6 + ft_count_digits(block.size.x) + 1]);
		ft_swap(&block.size.x, &block.size.y);
	}
	free(line);
	block.shape = get_block_shape(block.size);
	print_block(block, STDOUT_FILENO);
	return (block);
}
