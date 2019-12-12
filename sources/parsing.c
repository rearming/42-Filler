#include "filler.h"

void		get_player_and_enemy(char *line, char *out_player, char *out_enemy)
{
	if ((ft_strncmp("$$$ exec p", line, 10)) != CMP_SUCCESS)
		raise_error(ERR_INVALID_INIT_STR);
	if (line[10] == '1')
	{
		*out_player = 'O';
		*out_enemy = 'X';
	}
	else if (line[10] == '2')
	{
		*out_player = 'X';
		*out_enemy = 'O';
	}
	else
		raise_error(ERR_INVALID_PLAYER_NUMBER);
}

