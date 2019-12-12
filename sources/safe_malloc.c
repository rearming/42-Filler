#include <stddef.h>
#include <stdlib.h>
#include "filler_defines.h"

void	*safe_malloc(size_t size, void (*exit_func)(int))
{
	void	*allocated;

	allocated = malloc(size);
	if (!allocated)
		exit_func(ERR_MALLOC);
	return (allocated);
}
