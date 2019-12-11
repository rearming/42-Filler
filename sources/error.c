#include "filler.h"

void	raise_error(int err_code)
{
	if (err_code == ERR_INVALID_INIT_STR)
		ft_printf_fd(STDERR_FILENO, "invalid "
						"init ($$$ exec p...) line!\n");
	if (err_code == ERR_INVALID_PLAYER_NUMBER)
		ft_printf_fd(STDERR_FILENO, "Invalid player number!\n");
	if (err_code == ERR_INVALID_MAP_SIZE)
		ft_printf_fd(STDERR_FILENO, "Invalid map size!\n");
	if (err_code == ERR_MALLOC)
		ft_printf_fd(STDERR_FILENO, "malloc() failed!\n");
	exit(err_code);
}
