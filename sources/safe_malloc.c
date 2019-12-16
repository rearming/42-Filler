/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:29:52 by sleonard          #+#    #+#             */
/*   Updated: 2019/12/16 15:29:53 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
