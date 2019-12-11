#include <stddef.h>
#include <stdlib.h>

void	*safe_malloc(size_t size, void (*exit_func)(int), int err_code)
{
	void	*allocated;

	allocated = malloc(size);
	if (!allocated)
		exit_func(err_code);
	return (allocated);
}
